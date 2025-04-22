import os
EXCLUDED_FOLDERS = [".git", "scraps", ".vscode"]

def folder_mapping(path, out='', t=0, printout=False):
    """
    - t: int, default=0, number of tabs as prefix
    - printout: bool, default=False, print the path/file
    """
    t_next = t + 1
    for folder_path, subfolders, files in os.walk(path):
        # Exclude folders in-place
        subfolders[:] = [d for d in subfolders if d not in EXCLUDED_FOLDERS]

        s = "\t" * t + f"Folder: {folder_path}"
        out += s + '\n'
        if printout:
            print(s)

        for file in files:
            s = "\t" * t + f"- {file}"
            out += s + '\n'
            if printout:
                print(s)

        # Recursively call for remaining subfolders
        for subfolder in subfolders:
            subpath = os.path.join(folder_path, subfolder)
            out += folder_mapping(subpath,
                                    t=t_next,
                                    printout=printout)
    return out

if __name__ == "__main__":
    folder_path = os.path.join(os.path.dirname(__file__), '..')
    out = folder_mapping(folder_path, printout=False)
    with open("folder_tree.txt", 'w') as f:
        f.write(out)