# Address Book Management System

A console-based address book application written in C. It lets you add, view, search, edit, delete, and sort contacts, then save contact data to a file. The program starts with fictional sample contacts.

## Features

- Add and list contacts
- Search by name, phone number, or email
- Edit and delete contacts
- Sort contacts by name, phone number, or email
- Save contacts to a file
- Validate contact details

## Requirements

- GCC or another C compiler

## Build

From the project directory, compile the source files:

```bash
gcc -o address_book main.c contact.c file.c populate.c
```

## Run

```bash
./address_book
```

Follow the menu prompts to manage contacts. Choose **6** to save contacts, or **7** to exit.

## Sample Data

The repository includes fictional sample contacts for demonstration. Replace them with your own data when running the program; avoid committing real contact information to a public repository.
