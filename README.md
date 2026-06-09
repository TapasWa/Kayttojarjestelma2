# Unix Utilities (my-cat, my-grep, my-zip, my-unzip)

Short project implementing simple UNIX utilities for an assignment.

Files
- `my-cat.c` — prints one or more files.
- `my-grep.c` — searches for a case-sensitive term in files or stdin; supports arbitrarily long lines.
- `my-zip.c` — run-length encodes input to a binary format (4-byte little-endian count + 1 byte value per run).
- `my-unzip.c` — decodes the compressed format back to the original byte stream.
- `submission.md` — short summary and screenshot instructions.

Build
```powershell
gcc -o my-cat.exe my-cat.c -Wall -Werror
gcc -o my-grep.exe my-grep.c -Wall -Werror
gcc -o my-zip.exe my-zip.c -Wall -Werror
gcc -o my-unzip.exe my-unzip.c -Wall -Werror
```

Quick run (example test file creation):
```powershell
$text = "aaaabbb`nfoo bar`nlast line`n"
[System.IO.File]::WriteAllText('sample.txt', $text, [System.Text.Encoding]::ASCII)

.\my-cat.exe sample.txt
.\my-grep.exe foo sample.txt

# create compressed file (binary-safe capture) and show decompressed output
# see submission.md for the full binary-safe PowerShell capture examples
.\my-unzip.exe sample.z
```

Notes
- On Windows, these programs were built and tested with GCC. `my-zip`/`my-unzip` set stdout to binary mode on Windows to avoid CRLF translation.
- The repository currently contains compiled binaries for convenience; you may remove them and add the executables to `.gitignore` if desired.

Repository: https://github.com/TapasWa/Kayttojarjestelma3
