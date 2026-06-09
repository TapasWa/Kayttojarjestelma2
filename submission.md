# Unix Utilities Submission

## Short Summary
Implemented the four required UNIX utilities in C:
- `my-cat.c` prints one or more files in order and reports open failures with the required message.
- `my-grep.c` searches for a case-sensitive term in files or standard input and handles long lines safely.
- `my-zip.c` compresses input using run-length encoding with the required 4-byte integer plus character format.
- `my-unzip.c` reverses the compressed format and restores the original byte stream.

## Validation
- All four programs compile with `gcc -Wall -Werror`.
- `my-cat` and `my-grep` were tested on sample text input.
- `my-zip` and `my-unzip` were verified with a round-trip binary test using raw process capture on Windows.

## Screenshots
Add screenshots of the working utilities here before submission.

- `my-cat` screenshot: pending
- `my-grep` screenshot: pending
- `my-zip` screenshot: pending
- `my-unzip` screenshot: pending

## Repository
Public repository URL: https://github.com/TapasWa/Kayttojarjestelma3

## Notes
The workspace currently contains the required source files as separate single-file utilities:
- `my-cat.c`
- `my-grep.c`
- `my-zip.c`
- `my-unzip.c`

## Run and Screenshot Commands
Run these commands from PowerShell while in the project folder to produce on-screen output suitable for screenshots and to create verification files.

1) Build (optional — already built in this workspace):
```powershell
gcc -o my-cat.exe my-cat.c -Wall -Werror
gcc -o my-grep.exe my-grep.c -Wall -Werror
gcc -o my-zip.exe my-zip.c -Wall -Werror
gcc -o my-unzip.exe my-unzip.c -Wall -Werror
```

2) Create a test file (ASCII):
```powershell
$text = "aaaabbb`nfoo bar`nlast line`n"
[System.IO.File]::WriteAllText('sample.txt', $text, [System.Text.Encoding]::ASCII)
```

3) Show `my-cat` output (for screenshot):
```powershell
.\my-cat.exe sample.txt
```

4) Show `my-grep` output (for screenshot):
```powershell
.\my-grep.exe foo sample.txt
```

5) Create compressed file (binary-safe) and show `my-unzip` output (for screenshot):
```powershell
# Create sample.z (binary-safe capture)
$pi = New-Object System.Diagnostics.ProcessStartInfo
$pi.FileName = (Join-Path (Get-Location) 'my-zip.exe')
$pi.Arguments = 'sample.txt'
$pi.UseShellExecute = $false
$pi.RedirectStandardOutput = $true
$p = [System.Diagnostics.Process]::Start($pi)
$fs=[System.IO.File]::Open('sample.z',[System.IO.FileMode]::Create,[System.IO.FileAccess]::Write)
$p.StandardOutput.BaseStream.CopyTo($fs)
$fs.Close(); $p.WaitForExit()

# Decompress to stdout (prints contents)
$pi2 = New-Object System.Diagnostics.ProcessStartInfo
$pi2.FileName = (Join-Path (Get-Location) 'my-unzip.exe')
$pi2.Arguments = 'sample.z'
$pi2.UseShellExecute = $false
$pi2.RedirectStandardOutput = $true
$p2 = [System.Diagnostics.Process]::Start($pi2)
[Console]::OpenStandardOutput().Write((New-Object System.IO.StreamReader($p2.StandardOutput.BaseStream)).ReadToEnd())
$p2.WaitForExit()
```

6) Optional: create verification files and compare (good for a screenshot showing equality):
```powershell
# write decompressed file
[System.Diagnostics.Process]::Start($pi2) | Out-Null
#$p2.StandardOutput.BaseStream.CopyTo([System.IO.File]::Open('roundtrip.txt',[System.IO.FileMode]::Create,[System.IO.FileAccess]::Write))
# compare
fc sample.txt roundtrip.txt
```

Notes on screenshots: run each command so the output appears in the terminal and then capture the terminal window using Snipping Tool or Win+Shift+S. Save images and insert them into your submission document.
