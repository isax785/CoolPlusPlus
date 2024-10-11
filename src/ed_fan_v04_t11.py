import numpy as np
import numpy.polynomial.polynomial as poly
from statistics import mean
from math import sqrt
from scipy.optimize import curve_fit
# import matplotlib.pyplot as plt
from copy import deepcopy


class Fan:
    def __init__(self, curves):
        """
        Measurement units:
        - n : [1/min]
        - pow : [W]
        - u : [m3/h]
        - dp : [Pa]
        - n0100 : (0-1) [-]

        :param curves: input dictionary with all the fan curves.
            _rpm : Iso-rpm curves.
                   See n0100_rpm values to know the rpm belonging to each curve.
            _loss : Iso-kv (i.e. circuit geometry that generates dp) curves.
                    The first curve in the list belongs to the circuit with higher pressures.
        """
        self.n_rpm = curves['rpm']['n_rpm']
        self.n_loss = curves['loss']['n_loss']
        self.n_max = self.n_rpm[0][0]
        self.n0100_rpm = curves['rpm']['n0100_rpm']
        self.n0100_loss = curves['loss']['n0100_loss']
        self.lw_ref = curves['lw']
        self.volt_ref = curves['volt']
        self.n0100_min = self.n0100_loss[0][-2]  # the lowest rpm value by excluding 0
        
        self.pow_rpm_orig = curves['rpm']['pow_rpm']
        self.u_rpm_orig = curves['rpm']['u_rpm']
        self.dp_rpm_orig = curves['rpm']['dp_rpm']
        self.lw_rpm_orig = curves['rpm']['lw_rpm']
        self.cur_rpm_orig = curves['rpm']['cur_rpm']
        
        self.pow_loss_orig = curves['loss']['pow_loss']
        self.u_loss_orig = curves['loss']['u_loss']
        self.dp_loss_orig = curves['loss']['dp_loss']
        self.lw_loss_orig = curves['loss']['lw_loss']
        self.cur_loss_orig = curves['loss']['cur_loss']
        
        self.u_rpm = deepcopy(self.u_rpm_orig)
        self.dp_rpm = deepcopy(self.dp_rpm_orig)
        self.pow_rpm = deepcopy(self.pow_rpm_orig)        
        self.lw_rpm = deepcopy(self.lw_rpm_orig)
        self.cur_rpm = deepcopy(self.cur_rpm_orig)
        self.u_loss = deepcopy(self.u_loss_orig)
        self.dp_loss = deepcopy(self.dp_loss_orig)
        self.pow_loss = deepcopy(self.pow_loss_orig)
        self.lw_loss = deepcopy(self.lw_loss_orig)
        self.cur_loss = deepcopy(self.cur_loss_orig)
        
        self.fan_type = curves.get('fan_type', 'EC')
        
        self.deg = 2 
        
        self._new_points()
        
    def _new_points(self):
        """ 
        Find points in the curves with the same kv
        """
        u_100 = self.u_rpm[0]
        dp_100 = self.dp_rpm[0]

        for i in range(1, len(self.u_rpm)):
            u_rpm_i = self.u_rpm[i]
            dp_rpm_i = self.dp_rpm[i]
            pow_rpm_i = self.pow_rpm[i]
            lw_rpm_i = self.lw_rpm[i]
            cur_rpm_i = self.cur_rpm[i]
            
            for k in range(len(u_100)):
                if dp_100[k] != 0 and dp_rpm_i[k] != 0:
                    kv = u_100[k] / (dp_100[k] ** 0.5)
                    if u_rpm_i[k] / (dp_rpm_i[k] ** 0.5) != kv: 
                        u_i, dp_i = self._inters_new_u(u_rpm_i, dp_rpm_i, kv)
                        pow_i = poly.polyval(u_i, poly.polyfit(u_rpm_i, pow_rpm_i, self.deg))
                        lw_i = poly.polyval(u_i, poly.polyfit(u_rpm_i, lw_rpm_i, self.deg))
                        cur_i = poly.polyval(u_i, poly.polyfit(u_rpm_i, cur_rpm_i, self.deg))
                        self.u_rpm[i][k] = u_i
                        self.dp_rpm[i][k] = dp_i
                        self.pow_rpm[i][k] = pow_i
                        self.lw_rpm[i][k] = lw_i
                        self.cur_rpm[i][k] = cur_i
                        self.u_loss[k][i] = u_i
                        self.dp_loss[k][i] = dp_i
                        self.pow_loss[k][i] = pow_i
                        self.lw_loss[k][i] = lw_i
                        self.cur_loss[k][i] = cur_i
                        
    def _inters_new_u(self, u_rpm_i, dp_rpm_i, kv):
        """
        Find u and dp with a fixed kv in the curve u_rpm_i - dp_rpm_i
        """
        u = max(u_rpm_i)
        err_pre = 100
        delta = 1000
        delta_scaling = 0.5
        while True:
            dp = poly.polyval(u, poly.polyfit(u_rpm_i, dp_rpm_i, self.deg))
            dp_kv = (u / kv) ** 2
            err = dp - dp_kv
            
            if abs(err) < 0.01:
                break
            
            if err * err_pre < 0:
                delta *= delta_scaling
            if err > 0:
                u += delta
            else:
                u -= delta
            err_pre = err
        
        return u, dp       
    
    def _interp_u_rpm(self, n0100):
        """ Find list of u with at n0100 partial load"""
        if n0100 in self.n0100_loss[0]:
            i = self.n0100_loss[0].index(n0100)
            u_in = self.u_rpm[i]
        else:
            n0100_high = 1
            n0100_low = 0
            i_low = i_high = 0
            for i, n in enumerate(self.n0100_loss[0]):
                if n > n0100 and n < n0100_high:
                    n0100_high = n
                    i_high = i
                if n < n0100 and n > n0100_low:
                    n0100_low = n
                    i_low = i
            u_low = self.u_rpm[i_low] if n0100_low != 0 else [0, 0, 0, 0] 
            u_high = self.u_rpm[i_high]
            u_in = []
            for i in range(len(u_low)):
                u_in.append(u_low[i] + (u_high[i] - u_low[i]) * (n0100 - n0100_low) / (n0100_high - n0100_low))
        return u_in

    def new_curve(self, n0100, fan_machine=None):
        """ Find new curves at partial load depending on the fan type in the machine"""
        if fan_machine is None: fan_machine = self.fan_type
        if self.fan_type in ['AC', 'TC']:
            if fan_machine == 'TC':
                self._new_curve_tc(n0100)
            else:
                self._new_curve_tc(1)
        else:
            self._new_curve_ec(n0100)
    
    def _new_curve_ec(self, n0100):
        """ Find new curves in case of EC fan"""
        self.u_in = self._interp_u_rpm(n0100)  # interpolation of the flowrate (i.e. u, abscissa) values
        if n0100 == 1:
            i = self.n0100_loss[0].index(n0100)
            self.dp_in = self.dp_rpm[i]
            self.pow_in = self.pow_rpm[i]
            self.lw_in = self.lw_rpm[i]
            if self.cur_rpm[i][0] == 0 or self.cur_rpm[i][0] is None:
                self.cur_in = [k / (0.9 * sqrt(3) * self.volt_ref) for k in self.pow_in]
            else:
                self.cur_in = self.cur_rpm[i]
        else:
            self.dp_in, self.pow_in, self.lw_in, self.cur_in = [], [], [], []  # point list of the new curves
            for i in range(len(self.u_loss)):
                self.pow_in.append(self.pow_loss[i][0]/(self.u_loss[i][0] ** 3) * (self.u_in[i] ** 3))
                if self.n0100_rpm[1][0] == 0 or self.n0100_rpm[1][0] is None:
                    self.dp_in.append(self.dp_loss[i][0]/(self.u_loss[i][0] ** 2) * (self.u_in[i] ** 2))
                    self.lw_in = self.lw_rpm[i]
                    self.cur_in.append(self.pow_in[i] / (0.9 * sqrt(3) * self.volt_ref))
                else:
                    self.dp_in.append(poly.polyval(self.u_in[i], poly.polyfit(self.u_loss[i], self.dp_loss[i], self.deg)))
                    self.lw_in.append(poly.polyval(self.u_in[i], poly.polyfit(self.u_loss[i][:-1], self.lw_loss[i][:-1], 1)))
                    if self.cur_rpm[0][0] == 0 or self.cur_rpm[0][0] is None:
                        pf = 0.9
                    else:
                        for j in range(len(self.n0100_loss[0])):
                            if self.n0100_loss[0][j] <= n0100:
                                break
                        pf_2 = mean([self.pow_rpm[j-1][k] / (self.cur_rpm[j-1][k] * self.volt_ref * sqrt(3)) for k in range(len(self.pow_rpm[j-1]))])
                        if j == len(self.n0100_loss[0]) - 1:
                            pf = pf_2
                        else:
                            pf_1 = mean([self.pow_rpm[j][k] / (self.cur_rpm[j][k] * self.volt_ref * sqrt(3)) for k in range(len(self.pow_rpm[j]))])
                            pf = (pf_2 - pf_1) / (self.n0100_loss[0][j-1] - self.n0100_loss[0][j]) * (n0100 - self.n0100_loss[0][j]) + pf_1
                    self.cur_in.append(self.pow_in[i]/(pf * sqrt(3) * self.volt_ref))

        return self.u_in, self.dp_in, self.pow_in, self.lw_in, self.cur_in

    def _new_curve_tc(self, n0100):
        """ Find new curves in case of AC/TC fan"""
        if n0100 == 1:
            self.u_in = self.u_loss[0][:-1]
            self.dp_in = self.dp_loss[0][:-1]
            self.n_in = self.n_loss[0][:-1]
            self.pow_in = self.pow_loss[0][:-1]
            self.lw_in = self.lw_loss[0][:-1]
            self.cur_in = self.cur_loss[0][:-1]
        else:
            self.u_in, self.dp_in, self.n_in, self.pow_in, self.lw_in, self.cur_in = [], [], [], [], [], []
            for i in range(len(self.u_loss[0])):
                if i != len(self.u_loss[0]) - 1:
                    u = self.u_loss[0][i] * n0100
                    self.u_in.append(u)
                    self.dp_in.append(self.dp_loss[0][i] / (self.u_loss[0][i] ** 2) * (u ** 2))
                    self.n_in.append(self.n_loss[0][i] * n0100)
                    self.pow_in.append(self.pow_loss[0][i] / (self.u_loss[0][i] ** 3) * (u ** 3))
                    self.lw_in.append(self.lw_loss[0][i])
                    self.cur_in.append(self.cur_loss[0][i] / (self.u_loss[0][i] ** 3) * (u ** 3))

    def perf(self, settings):
        method = settings['method']
        self.n0100 = settings['n0100']
        self.volt = settings['volt']
        self.u = settings.get('u')
        self.dp = settings.get('dp')
        self.pow = settings.get('pow')
        self.calc_curve = settings.get('calc_curve', True)
        fan_machine = settings.get('fan_machine', self.fan_type)
        if self.calc_curve:
            self.new_curve(self.n0100, fan_machine)
        if method == 'perf_u':
            self._perf_u()
        elif method == 'perf_dp':
            self._perf_dp()
        elif method == 'perf_pow':
            self._perf_pow()
        else:
            raise ValueError('The method does not exist!')
        
        if fan_machine == 'AC':
            self.u *= self.n0100
            self.dp *= self.n0100
            self.n *= self.n0100
            self.pow *= self.n0100
            self.lw *= self.n0100
            self.cur *= self.n0100
                    
    def _interp_fix(self, val, lst_val, lst_res):
        """ Interpolate values in case of AC/TC fan"""
        val_low, val_up = lst_val[0], lst_val[-1]
        for i in lst_val:
            val_up = i if val_up <= i <= val else val_up
            val_low = i if val <= i <= val_low else val_low
        i_up = lst_val.index(val_up)
        i_low = lst_val.index(val_low)
        if val_up == val_low:
            return lst_res[i_up]
        else:
            part = (val - val_low) / (val_up - val_low)
            return part * (lst_res[i_up] - lst_res[i_low]) + lst_res[i_low]
        
    def _perf_u(self):
        "Performance starting from a u (i.e. flow rate [m3/h]) value."
        if self.fan_type not in ['AC', 'TC']:
            self.n = self.n_max * self.n0100
            self.dp = poly.polyval(self.u, poly.polyfit(self.u_in, self.dp_in, self.deg))
            self.pow = poly.polyval(self.u, poly.polyfit(self.u_in, self.pow_in, self.deg))
            self.lw = poly.polyval(self.u, poly.polyfit(self.u_in, self.lw_in, self.deg))
            cur = poly.polyval(self.u, poly.polyfit(self.u_in, self.cur_in, self.deg))
        else:
            self.n = self._interp_fix(self.u, self.u_in, self.n_in)
            self.dp = self._interp_fix(self.u, self.u_in, self.dp_in)
            self.pow = self._interp_fix(self.u, self.u_in, self.pow_in)
            self.lw = self._interp_fix(self.u, self.u_in, self.lw_in)
            cur = self._interp_fix(self.u, self.u_in, self.cur_in)

        self.cur = cur * self.volt_ref / self.volt
    
    def _perf_dp(self):
        "Performance starting from a dp (i.e. pressure [Pa]) value."
        if self.fan_type not in ['AC', 'TC']:
            self.n = self.n_max * self.n0100
            self.u = poly.polyval(self.dp, poly.polyfit(self.dp_in, self.u_in, self.deg))  # x and y are swapped
            self.pow = poly.polyval(self.u, poly.polyfit(self.u_in, self.pow_in, self.deg))
            self.lw = poly.polyval(self.u, poly.polyfit(self.u_in, self.lw_in, self.deg))
            cur = poly.polyval(self.u, poly.polyfit(self.u_in, self.cur_in, self.deg))
        else:
            self.u = self._interp_fix(self.dp, self.pow_in, self.u_in)
            self.n = self._interp_fix(self.u, self.u_in, self.n_in)
            self.pow = self._interp_fix(self.u, self.u_in, self.pow_in)
            self.lw = self._interp_fix(self.u, self.u_in, self.lw_in)
            cur = self._interp_fix(self.u, self.u_in, self.cur_in)

        self.cur = cur * self.volt_ref / self.volt

    def _perf_pow(self):
        "Performance starting from a pow (i.e. power [W]) value."
        if self.fan_type not in ['AC', 'TC']:
            self.n = self.n_max * self.n0100
            self.u = poly.polyval(self.pow, poly.polyfit(self.pow_in, self.u_in, self.deg))  # x and y are swapped
            self.dp = poly.polyval(self.u, poly.polyfit(self.u_in, self.dp_in, self.deg))
            self.lw = poly.polyval(self.u, poly.polyfit(self.u_in, self.lw_in, self.deg))
            cur = poly.polyval(self.u, poly.polyfit(self.u_in, self.cur_in, self.deg))
        else:
            self.u = self._interp_fix(self.pow, self.pow_in, self.u_in)
            self.n = self._interp_fix(self.u, self.u_in, self.n_in)
            self.dp = self._interp_fix(self.u, self.u_in, self.dp_in)
            self.lw = self._interp_fix(self.u, self.u_in, self.lw_in)
            cur = self._interp_fix(self.u, self.u_in, self.cur_in)

        self.cur = cur * self.volt_ref / self.volt

    # def check_curves_plot(self):
    #     n0100_ten_curves = np.linspace(0, 1, 11)
    #     u_in_list, dp_in_list, pow_in_list = [], [], []
    #
    #     for n0100 in n0100_ten_curves:
    #         self.new_curve(n0100)
    #         u_in_list.append(self.u_in)
    #         dp_in_list.append(self.dp_in)
    #         pow_in_list.append(self.pow_in)
    #
    #     n0100_given_curves = self.n0100_loss[0]
    #     u_in_list_start, dp_in_list_start, pow_in_list_start = [], [], []
    #
    #     for n0100 in n0100_given_curves:
    #         self.new_curve(n0100)
    #         u_in_list_start.append(self.u_in)
    #         dp_in_list_start.append(self.dp_in)
    #         pow_in_list_start.append(self.pow_in)
    #
    #     fig = plt.figure(1)
    #     ax1 = fig.add_subplot(211)
    #     for i in range(len(self.u_rpm)):
    #         ax1.plot(self.u_rpm[i], self.dp_rpm[i], color='silver')
    #     for i in range(len(self.u_loss)):
    #         ax1.plot(self.u_loss[i], self.dp_loss[i], color='silver')
    #     for i, u_in in enumerate(u_in_list):
    #         ax1.plot(u_in, dp_in_list[i], '*--r')
    #     for i, u_in in enumerate(u_in_list_start):
    #         ax1.plot(u_in, dp_in_list_start[i], '*--b')
    #     ax1.grid()
    #     ax1.set_title('u-dp', fontsize=16)
    #     ax2 = fig.add_subplot(212)
    #     for i in range(len(self.u_rpm)):
    #         ax2.plot(self.u_rpm[i], self.pow_rpm[i], color='silver')
    #     for i in range(len(self.u_loss)):
    #         ax2.plot(self.u_loss[i], self.pow_loss[i], color='silver')
    #     for i, u_in in enumerate(u_in_list):
    #         ax2.plot(u_in, pow_in_list[i], '*--r')
    #     for i, u_in in enumerate(u_in_list_start):
    #         ax2.plot(u_in, pow_in_list_start[i], '*--b')
    #     ax2.grid()
    #     ax2.set_title('u-pow', fontsize=16)
    #     plt.show()
    #
    # def check_operating_point(self, n0100_work, u, dp, W, u_range, dp_range):
    #     n0100_ten_curves = np.linspace(0, 1, 11)
    #     u_in_list, dp_in_list, pow_in_list = [], [], []
    #
    #     for n0100 in n0100_ten_curves:
    #         self.new_curve(n0100)
    #         u_in_list.append(self.u_in)
    #         dp_in_list.append(self.dp_in)
    #         pow_in_list.append(self.pow_in)
    #
    #     "Rearrange iso-loss curves"
    #     u_in_list_loss, dp_in_list_loss, pow_in_list_loss = [], [], []
    #     for i in range(len(u_in_list[0])):
    #         u_in_list_loss.append([])
    #         dp_in_list_loss.append([])
    #         pow_in_list_loss.append([])
    #
    #     for i, row in enumerate(u_in_list):
    #         for j, val in enumerate(row):
    #             u_in_list_loss[j].append(val)
    #             dp_in_list_loss[j].append(dp_in_list[i][j])
    #             pow_in_list_loss[j].append(pow_in_list[i][j])
    #
    #     fig = plt.figure(1)
    #     ax1 = fig.add_subplot(211)
    #     for i, u_in in enumerate(u_in_list):
    #         ax1.plot(u_in, dp_in_list[i], color='silver')
    #     for i, u_in in enumerate(u_in_list_loss):
    #         ax1.plot(u_in, dp_in_list_loss[i], color='silver')
    #     ax1.plot(u, dp, color='black', marker="o")
    #     fan.new_curve(self, n0100_work)
    #     ax1.plot(self.u_in, self.dp_in, color='black')
    #     ax1.plot(u_range, dp_range, color='black')
    #     ax1.grid()
    #     ax1.set_title('u-dp', fontsize=16)
    #     ax2 = fig.add_subplot(212)
    #     for i, u_in in enumerate(u_in_list):
    #         ax2.plot(u_in, pow_in_list[i], color='silver')
    #     for i, u_in in enumerate(u_in_list_loss):
    #         ax2.plot(u_in, pow_in_list_loss[i], color='silver')
    #     ax2.plot(u, W, color='black', marker="o")
    #     ax2.plot(self.u_in, self.pow_in, color='black')
    #     ax2.grid()
    #     ax2.set_title('u-pow', fontsize=16)
    #     plt.show()


if __name__ == '__main__':
    from obj import browse_folder as bf
    from obj import data_import as di

    file_path = bf.sup_folder(1) + '\\tables' + '\\' + 'EBM_fan_datasheet_A3_2171.xlsx'
    crv_rpm, crv_loss = di.ebm_data(file_path, sheet_nr=0)

    fan = Fan({'rpm': crv_rpm, 'loss': crv_loss})
    # u = 29510  # [m3/h]
    # n0100 = 0.9  # [0-1]
    n_max = fan.n_max
    speed_arr = [127, 191, 249, 312, 377, 442, 506, 569, 630, 691, 752, 805, 867, 925, 980, 1035, 1085, 1130]
    # pow_arr = [26.9, 35.9, 51, 75.6, 111.4, 159.7, 222, 299.9, 391.7, 501.18, 633.4, 749.6, 926.3, 1111.7, 1316.4, 1540.4, 1772.7, 1991.9]
    # pow_arr = [20, 29, 44, 68, 104, 151.5, 212, 290, 381, 490, 624, 740, 918, 1104, 1310, 1536, 1768, 1982]
    pow_arr = [10, 27, 47, 75, 115, 160, 210, 270, 325, 455, 605, 750, 935, 1130, 1330, 1550.4, 1772.7, 2000]
    # pow_arr = [15, 30, 45, 65, 90, 130, 180, 245, 619, 745, 882, 1010, 1172, 1335, 1498, 1671, 1836, 2002]

    # speed_arr = [600, 800, 1000, 1130]
    # pow_arr = [263, 623, 1217, 1775]

    u_arr = []
    dp_arr = []
    # pow_arr = []

    for i in range(0, len(speed_arr)):
        speed = speed_arr[i]
        pow = pow_arr[i]
        # pow = 0.00000137582424286851*speed**3 -0.000145201277484816*speed**2 + 0.165602385077512*speed
        # pow = -0.00000000000000435154012525924*speed**6 + 0.0000000000152063878745455*speed**5 + -0.0000000201226928846076*speed**4 +0.0000138064944979965*speed**3 -0.00365685326274122*speed**2 + 0.516742160665291*speed

        n0100 = speed / n_max

        fan.new_curve(n0100)
        # print('u: {}\ndp: {}\npow: {}'.format(fan.u_in,
        #                                       fan.dp_in,
        #                                       fan.pow_in))

        # dp, pow = fan.perf_u(n0100, u)
        # print('pl: {:.2f} - u: {:.2f} - dp: {:.2f} - pow: {:.2f}'.format(n0100, u, dp, pow))
        #
        # u, pow = fan.perf_dp(n0100, dp)
        # print('pl: {:.2f} - u: {:.2f} - dp: {:.2f} - pow: {:.2f}'.format(n0100, u, dp, pow))

        u, dp = fan.perf_pow(n0100, pow)
        u_arr.append(round(u, 2))
        dp_arr.append(round(dp, 2))
        # pow_arr.append(round(pow, 2))
        # print('pl: {:.2f} - u: {:.2f} - dp: {:.2f} - pow: {:.2f}'.format(n0100, u, dp, pow))

    print(u_arr)
    print(dp_arr)
    # fan.check_curves_plot()

    fig = plt.figure(1)
    plt.plot(u_arr, dp_arr)
    plt.show()
    fig1 = plt.figure(2)
    plt.plot(u_arr, pow_arr)
    plt.show()
