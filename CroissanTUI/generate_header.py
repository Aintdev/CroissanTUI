import re
from pathlib import Path

output_lines = ["#pragma once", "// CroissanTUI - Single Header Library", "// Auto-generated\n"]
seen_files = set()
seen_system = set()

def process_file(path):
    path = Path(path)
    real = str(path.resolve())
    if real in seen_files:
        return
    seen_files.add(real)

    with open(path, "r") as f:
        for line in f:
            stripped = line.rstrip()

            if "#pragma once" in stripped:
                continue

            # lokale includes rekursiv auflösen
            m_local = re.match(r'#include\s+"([^"]+)"', stripped)
            if m_local:
                included = (path.parent / m_local.group(1)).resolve()
                process_file(included)
                continue

            # system includes deduplizieren
            m_sys = re.match(r'#include\s+<([^>]+)>', stripped)
            if m_sys:
                if m_sys.group(1) in seen_system:
                    continue
                seen_system.add(m_sys.group(1))

            output_lines.append(stripped)

process_file("src/ctui.h")

with open("include/ctui_c.h", "w") as f:
    f.write("\n".join(output_lines))

print("ctui_c.h generated!", len(output_lines), "lines generated.")