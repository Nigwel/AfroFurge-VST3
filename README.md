# AFROGRID Windows VST3 — development checkpoint 0.2

## Status (2026-10-13)
**Windows build recipe authored, NOT compiled on Windows, installer NOT produced or validated.** The local Linux machine has no Windows cross-compiler and cannot reach GitHub to fetch JUCE. The standalone DSP core has a Linux smoke test.

## Build on Windows (Visual Studio 2022 + CMake + Git + NSIS)
1. Open this project in a GitHub repository and run **Actions → Windows VST3 build and installer → Run workflow**, or run locally:
2. `cmake -S . -B build -G "Visual Studio 17 2022" -A x64`
3. `cmake --build build --config Release --target AFROGRID_VST3`
4. Find `AFROGRID.vst3` under `build/AFROGRID_artefacts/Release/VST3/`.
5. Run `makensis /DVST3_SOURCE="<absolute path to AFROGRID.vst3>" installer\AFROGRID.nsi` from project root.
6. Install the generated `AFROGRID_Setup_Windows_x64.exe`, then rescan VST3 plug-ins in Ableton Live 11 Standard.

## Actual current functionality
- JUCE VST3 instrument shell, stereo generated audio, 110 BPM default, tempo range 98–115 BPM, level and enable parameters, generic UI, state persistence.
- Four procedural synthesized voices: kick, rim, high pulse, low pulse; fixed two-bar sequence with late rim and sparse syncopation.
- No external samples, network dependency, or licensed sample packs included.

## Known limitations and explicit non-claims
- This is an engineering alpha, not a release-quality Afrobeats instrument. Groove has not been listening-tested or approved.
- **No completed Windows VST3 binary or executable installer is in this archive.** The workflow is not yet CI-tested. Host compatibility, sound quality, export, arrangement, advanced groove and UI remain unverified/unimplemented.
- The generated installer currently copies a VST3 bundle only. Uninstall integration with Windows Apps & Features and code signing are not implemented.
- JUCE licensing must be reviewed before commercial distribution. GitHub Actions runners must have network access to download the pinned JUCE source.
- The installer defaults to the standard system VST3 path; changing its destination can prevent discovery.

## Next gate
Run Windows CI, fix any compile/package failures, run VST3 validator, load and render in Ableton Live 11 Standard, test install/uninstall, and only then mark the Windows build gate passed.
