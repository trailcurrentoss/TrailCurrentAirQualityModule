# TrailCurrent Air Quality Module

Air quality sensor module for monitoring environmental conditions including temperature, humidity, and air quality metrics. Part of the [TrailCurrent](https://trailcurrent.com) open-source vehicle platform.

## Hardware Overview

- **Function:** Environmental monitoring module combining temperature, humidity, and air quality sensing
- **Key Features:**
  - DHT22 temperature and humidity sensor
  - Air quality sensing capability
  - Compact design suitable for integration into larger systems
  - PlatformIO-based firmware for configuration and operation

## Hardware Requirements

### Components

- **Sensors:**
  - DHT22 temperature/humidity sensor
  - Air quality sensor module

- **Connectors:**
  - JST XH 4-pin connectors for power and signal distribution

### KiCAD Library Dependencies

This project uses the consolidated [TrailCurrentKiCADLibraries](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries).

**Setup:**

```bash
# Clone the library
git clone git@github.com:trailcurrentoss/TrailCurrentKiCADLibraries.git

# Set environment variables (add to ~/.bashrc or ~/.zshrc)
export TRAILCURRENT_SYMBOL_DIR="/path/to/TrailCurrentKiCADLibraries/symbols"
export TRAILCURRENT_FOOTPRINT_DIR="/path/to/TrailCurrentKiCADLibraries/footprints"
export TRAILCURRENT_3DMODEL_DIR="/path/to/TrailCurrentKiCADLibraries/3d_models"
```

See [KICAD_ENVIRONMENT_SETUP.md](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries/blob/main/KICAD_ENVIRONMENT_SETUP.md) in the library repository for detailed setup instructions.

## Opening the Project

1. **Set up environment variables** (see Library Dependencies above)
2. **Open KiCAD:**
   ```bash
   kicad /path/to/EDA/TrailCurrentAirQualityModule/TrailCurrentAirQualityModule.kicad_pro
   ```
3. **Verify libraries load** - All symbol and footprint libraries should resolve without errors
4. **View 3D models** - Open PCB and press `Alt+3` to view the 3D visualization
   - All 3D models should load from the consolidated library path
   - Models use relative `${TRAILCURRENT_3DMODEL_DIR}` references

## Firmware

See `src/` directory for PlatformIO-based firmware.

**Setup:**
```bash
# Install PlatformIO (if not already installed)
pip install platformio

# Build firmware
pio run -d /path/to/project

# Upload to board
pio run -t upload -d /path/to/project
```

### Firmware Dependencies

This firmware depends on the following public libraries:

- **[C6SuperMiniRgbLedLibrary](https://github.com/trailcurrentoss/C6SuperMiniRgbLedLibrary)** (v0.0.1) - RGB LED status indicator driver
- **[Esp32C6OtaUpdateLibrary](https://github.com/trailcurrentoss/Esp32C6OtaUpdateLibrary)** (v0.0.1) - Over-the-air firmware update functionality
- **[Esp32C6TwaiTaskBasedLibrary](https://github.com/trailcurrentoss/Esp32C6TwaiTaskBasedLibrary)** (v0.0.3) - CAN bus communication interface
- **[Adafruit DHT sensor library](https://github.com/adafruit/DHT-sensor-library)** (v1.4.6+) - Temperature and humidity sensor

All dependencies are automatically resolved by PlatformIO during the build process.

**WiFi Credentials:**
- Firmware receives WiFi credentials via CAN Bus (ID 0x01) from the TrailCurrent system
- For standalone development/testing without the TrailCurrent system, create a `secrets.h` file in `src/`:
  ```cpp
  // Copy to src/secrets.h for local development only
  // NEVER commit this file - it's in .gitignore
  const char* ssid = "YOUR_SSID_HERE";
  const char* password = "YOUR_PASSWORD_HERE";
  ```

**Future Enhancement:** WiFi credential configuration will be fully implemented via CAN Bus protocol, allowing credentials to be distributed from the TrailCurrent system without firmware modifications.

## Manufacturing

- **PCB Files:** Ready for fabrication via standard PCB services (JLCPCB, OSH Park, etc.)
- **BOM Generation:** Export BOM from KiCAD schematic (Tools → Generate BOM)
- **JLCPCB Assembly:** This project supports automated assembly using JLCPCB
  - See [BOM_ASSEMBLY_WORKFLOW.md](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries/blob/main/BOM_ASSEMBLY_WORKFLOW.md) for detailed assembly workflow
  - Component library includes LCSC, Mouser, and DigiKey part numbers for flexible sourcing

## Documentation

- **Schematic:** EDA/TrailCurrentAirQualityModule/TrailCurrentAirQualityModule.kicad_sch
- **PCB Layout:** EDA/TrailCurrentAirQualityModule/TrailCurrentAirQualityModule.kicad_pcb

## License

MIT License - See LICENSE file for details

This is open source hardware. You are free to use, modify, and distribute these designs for personal or commercial purposes.

## Contributing

Improvements and contributions are welcome! Please submit issues or pull requests to the main repository.

## Support

For questions about:
- **KiCAD setup:** See [KICAD_ENVIRONMENT_SETUP.md](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries/blob/main/KICAD_ENVIRONMENT_SETUP.md)
- **Library consolidation:** See [CONNECTOR_CONSOLIDATION_SUMMARY.md](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries/blob/main/CONNECTOR_CONSOLIDATION_SUMMARY.md)
- **Assembly workflow:** See [BOM_ASSEMBLY_WORKFLOW.md](https://github.com/trailcurrentoss/TrailCurrentKiCADLibraries/blob/main/BOM_ASSEMBLY_WORKFLOW.md)
