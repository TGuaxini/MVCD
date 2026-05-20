from pathlib import Path
import json

ROOT = Path(__file__).resolve().parents[1]
SCREENSHOT_ROOT = ROOT / "docs" / "assets" / "screenshots"
OUTPUT = ROOT / "docs" / "data" / "evidence.json"

IMAGE_EXTENSIONS = {".png", ".jpg", ".jpeg", ".webp", ".gif"}

def pretty_name(path: Path) -> str:
    return path.stem.replace("_", " ").replace("-", " ")

def day_description(day_name: str) -> str:
    descriptions = {
        "Day_01": "Infrastructure setup evidence for the MVCD dissertation production pipeline.",
        "Day_02": "UE5 framework initialization evidence, including project setup, plugins, folders, and C++ architecture classes."
    }
    return descriptions.get(day_name, f"Evidence screenshots for {day_name.replace('_', ' ')}.")

def main():
    data = {}

    if not SCREENSHOT_ROOT.exists():
        print(f"No screenshot folder found: {SCREENSHOT_ROOT}")
        OUTPUT.parent.mkdir(parents=True, exist_ok=True)
        OUTPUT.write_text(json.dumps(data, indent=2), encoding="utf-8")
        return

    for day_folder in sorted(SCREENSHOT_ROOT.iterdir()):
        if not day_folder.is_dir():
            continue

        images = []
        for image in sorted(day_folder.iterdir()):
            if image.suffix.lower() in IMAGE_EXTENSIONS:
                rel_path = image.relative_to(ROOT / "docs").as_posix()
                images.append({
                    "file": f"./{rel_path}",
                    "caption": pretty_name(image)
                })

        if images:
            data[day_folder.name] = {
                "title": f"{day_folder.name.replace('_', ' ')} Evidence",
                "description": day_description(day_folder.name),
                "images": images
            }

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(json.dumps(data, indent=2), encoding="utf-8")
    print(f"Generated {OUTPUT}")
    print(f"Days found: {', '.join(data.keys()) if data else 'none'}")

if __name__ == "__main__":
    main()
