import sys

MAJOR_POINTS = 2
MINOR_POINTS = 1
MANDATORY_THRESHOLD = 14
BONUS_THRESHOLD = 19


def count_points(filename):
    major_count = 0
    minor_count = 0
    major_theoretical = 0
    minor_theoretical = 0

    try:
        with open(filename, "r", encoding="utf-8") as file:
            for line in file:
                line_lower = line.lower().strip()
                if not line_lower:
                    continue  # ignore empty lines

                is_theoretical = "(on going)" in line_lower

                if "major" in line_lower:
                    if is_theoretical:
                        major_theoretical += 1
                    else:
                        major_count += 1
                elif "minor" in line_lower:
                    if is_theoretical:
                        minor_theoretical += 1
                    else:
                        minor_count += 1

    except FileNotFoundError:
        print(f"Error: file '{filename}' not found.")
        sys.exit(1)

    total_points = major_count * MAJOR_POINTS + minor_count * MINOR_POINTS
    total_theoretical = major_theoretical * MAJOR_POINTS + minor_theoretical * MINOR_POINTS

    return (major_count, minor_count, total_points, total_theoretical)


def check_status(total_points):
    if total_points >= BONUS_THRESHOLD:
        return "🎉 Bonus reached!"
    elif total_points >= MANDATORY_THRESHOLD:
        return "✅ Mandatory reached!"
    else:
        return "❌ Mandatory not reached."


def main():
    if len(sys.argv) != 2:
        print("Usage: python count_points.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    major, minor, total, total_theo = count_points(filename)

    print("=== Completed Points ===")
    print(f"Major: {major} (x{MAJOR_POINTS} points)")
    print(f"Minor: {minor} (x{MINOR_POINTS} point)")
    print(f"Total points for now: {total}")
    print(f"Total theoretical points: {total + total_theo}")
    print(check_status(total))

if __name__ == "__main__":
    main()
