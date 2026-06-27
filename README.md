# OpenAG for Xash3D Android Mobile

**OpenAG-Xash3D-Mobile**, populer Half-Life promodu **OpenAG**'nin Xash3D Android mobil client icin port edilmis versiyonudur.

## Proje Hakkinda

Bu proje, OpenAG'nin tum kaynak kodlarini Xash3D mobil engine ile entegre ederek Android cihazlarda Adrenaline Gamer deneyimi sunmayi hedefler.

### Ozellikler

- **OpenAG Client (cl_dll)**: Tamamen Android'e uyarlanmis client DLL
- **OpenAG Server (dlls)**: Adrenaline Gamer oyun modu server DLL
- **Mobil Kontroller**: Xash3D touch input sistemi entegrasyonu
- **Discord Entegrasyonu**: Android'de otomatik devre disi (masaustunde aktif)
- **Steam Entegrasyonu**: Android'de otomatik devre disi (masaustunde aktif)
- **HUD & UI**: Mobil ekranlar icin optimize edilmis HUD
- **VGUI Destegi**: Xash3D vgui_support modulu ile tam entegrasyon

## Proje Yapisi

```
OpenAG-Xash3D-Mobile/
|-- cl_dll/                 # OpenAG Client DLL kaynaklari
|   |-- platform/android/   # Android input & platform katmani
|   |-- hl/                 # Half-Life silah & entity kodlari
|   |-- hud_*.cpp           # HUD elemanlari
|   |-- vgui_*.cpp          # VGUI arayuzleri
|-- dlls/                   # OpenAG Server DLL kaynaklari
|   |-- wpn_shared/         # Paylasilan silah kodlari
|-- common/                 # Ortak header'lar (Xash3D + OpenAG)
|-- engine/                 # Engine arayuzleri (Xash3D)
|-- game_shared/            # Paylasilan oyun kodlari
|-- pm_shared/              # Paylasilan fizik kodlari
|-- public/                 # Public API'lar
|-- external/               # Harici kutuphaneler
|-- utils/                  # Araclar (VGUI, vb.)
```

## Mobil Adaptasyon Katmani

### Platforma Ozel Kodlar

| Modul | Masaustu | Android | Aciklama |
|-------|----------|---------|----------|
| Input | `inputw32.cpp` | `input_android.cpp` | Touch kontrol sistemi |
| Discord | `discord_integration.cpp` | Stub | Discord Rich Presence |
| Steam ID | `steam_id.cpp` | Stub | Steam entegrasyonu |
| Update | `update_checker.cpp` | Stub | Guncelleme kontrolu |
| Ses | `soundsystem.cpp` | Xash3D Engine | OpenAL/SL ses sistemi |

### Android Input Sistemi

Xash3D'nin touch input sistemi kullanilarak su kontroller saglanir:

- **Sanal Joystick**: Hareket kontrolu (ileri/geri/sol/sag)
- **Swipe/Look**: Bakis acisi kontrolu
- **Touch Butonlar**: Atis, ziplama, egilme, reload, use
- **Vibration**: Titreşim destegi (Xash3D mobil interface)

## Derleme

### Android (NDK)

```bash
# Ortam degiskenleri
export XASH3D_PATH=/path/to/xash3d
export HLSDK_PATH=/path/to/OpenAG-Xash3D-Mobile

# NDK ile derleme
cd $HLSDK_PATH
ndk-build

# veya CMake ile
cmake -B build -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-21
cmake --build build
```

### CMake (Masaustu)

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Kurulum

1. Derlenmis `client.so` ve `hl.so` dosyalarini Xash3D Android uygulamanizin `valve/` klasorune kopyalayin
2. Xash3D'yi baslatin ve OpenAG modunu secin
3. Mobil kontroller otomatik olarak aktif olacaktir

## Katki

Bu proje asagidaki acik kaynak projeleri temel alir:

- [OpenAG](https://github.com/YaLTeR/OpenAG) - OpenAG PC Client
- [Xash3D FWGS](https://github.com/FWGS/xash3d) - Xash3D Engine

## Lisans

- OpenAG: Valve SDK Lisansi
- Xash3D: GPLv3
- Bu proje: GPLv3 (Xash3D ile uyumlu)
