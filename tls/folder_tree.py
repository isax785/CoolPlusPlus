import os
EXCLUDED_FOLDERS = [".git", "scraps", ".vscode"]

def folder_mapping(path, out='', t=0, printout=False):
    """
    - t: int, default=0, number of tabs as prefix
    - printout: bool, default=False, print the path/file
    """
    t_next = t + 1
    for folder in os.walk(path):
        s = "\t" * t + f"Folder: {folder[0]}"
        out += s + '\n'
        if printout: print(s)
        subfolders = folder[1]
        for subfolder in subfolders:
            subpath = os.path.join(path, subfolder)
            if subfolder not in EXCLUDED_FOLDERS \
                and all([ef not in subpath for ef in EXCLUDED_FOLDERS]):
                # FIXME: some paths are not properly excluded
                out += folder_mapping(subpath, 
                               t=t_next, 
                               printout=printout)
        files = folder[2]
        for file in files:
            s = "\t" * t + f"- {file}"
            out += s + '\n'
            if printout: print(s)
    return out
    
if __name__ == "__main__":
    folder_path = os.path.join(os.path.dirname(__file__), '..')
    out = folder_mapping(folder_path, printout=False)
    with open("folder_tree.txt", 'w') as f: 
        f.write(out)