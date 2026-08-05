import re
from pathlib import Path

output_lines = ["#pragma once", "// CroissanTUI - Single Header Library", "// Auto-generated\n"]
seen_files = set()
seen_system = set()

def process_file(path, source_dir):
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
                candidate = (path.parent / m_local.group(1)).resolve()
                if not candidate.exists():
                    candidate = (source_dir / m_local.group(1)).resolve()
                process_file(candidate, source_dir)
                continue

            # system includes deduplizieren
            m_sys = re.match(r'#include\s+<([^>]+)>', stripped)
            if m_sys:
                if m_sys.group(1) in seen_system:
                    continue
                seen_system.add(m_sys.group(1))

            output_lines.append(stripped)


BASE_DIR = Path(__file__).resolve().parent
SOURCE_DIR = (BASE_DIR / ".." / "Source").resolve()
OUT_FILE = BASE_DIR / ".." / "Include" / "ctui_c.h"

process_file(SOURCE_DIR / "ctui.h", SOURCE_DIR)


OUT_FILE.parent.mkdir(parents=True, exist_ok=True)

with open(OUT_FILE, "w", encoding="utf-8") as f:
    f.write("\n".join(output_lines))

print("ctui_c.h generated!", len(output_lines), "lines generated to path", OUT_FILE)