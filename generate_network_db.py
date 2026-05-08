import random


FIRST_NAMES = [
    "Aiden", "Maya", "Noah", "Sophia", "Ethan", "Olivia", "Liam", "Emma",
    "Lucas", "Ava", "Mason", "Isabella", "Logan", "Mia", "Elijah", "Amelia",
    "James", "Harper", "Benjamin", "Evelyn", "Daniel", "Luna", "Henry",
    "Grace", "Jack", "Chloe", "Leo", "Zoe", "Samuel", "Nora",
]

LAST_NAMES = [
    "Anderson", "Brown", "Clark", "Davis", "Evans", "Garcia", "Hall",
    "Johnson", "Kim", "Lee", "Lewis", "Martinez", "Miller", "Nguyen",
    "Patel", "Robinson", "Rodriguez", "Scott", "Smith", "Taylor",
    "Thomas", "Walker", "White", "Wilson", "Young",
]

COLLEGES = ["USC", "UCLA", "UC Berkeley", "Stanford", "Caltech", "UC Irvine"]
MAJORS = [
    "Computer Science", "Electrical Engineering", "Business", "Biology",
    "Mathematics", "Economics", "Data Science", "Psychology",
]
STATES = ["CA", "NY", "TX", "WA", "AZ", "NV", "OR"]
EMAIL_TYPES = ["School", "Work", "Personal", "Gmail", "Yahoo"]
PHONE_TYPES = ["Mobile", "Home", "Work"]


def phone_number():
    return f"{random.randint(200, 999)}-{random.randint(200, 999)}-{random.randint(1000, 9999)}"


def birthdate():
    return f"{random.randint(1, 12)}/{random.randint(1, 28)}/{random.randint(1970, 2007)}"


def make_email(first, last, index):
    return f"{first.lower()}.{last.lower()}{index}@example.com"


def main():
    random.seed(355)
    output_file = "networkDB_100.txt"
    used_names = set()
    people = []

    while len(people) < 500:
        first = random.choice(FIRST_NAMES)
        last = random.choice(LAST_NAMES)
        key = (first, last)

        if key in used_names:
            continue

        used_names.add(key)
        people.append((first, last))

    with open(output_file, "w", encoding="utf-8") as fout:
        for index, (first, last) in enumerate(people, start=1):
            fout.write(first + "\n")
            fout.write(last + "\n")
            fout.write(birthdate() + "\n")
            fout.write(f"({random.choice(EMAIL_TYPES)}) {make_email(first, last, index)}\n")
            fout.write(f"({random.choice(PHONE_TYPES)}) {phone_number()}\n")
            fout.write(f"college: {random.choice(COLLEGES)}\n")
            fout.write(f"major: {random.choice(MAJORS)}\n")
            fout.write(f"state: {random.choice(STATES)}\n")

            if index != len(people):
                fout.write("--------------------\n")

    print(f"Wrote {len(people)} people to {output_file}")


if __name__ == "__main__":
    main()
