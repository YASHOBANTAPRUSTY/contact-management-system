# contact-management-system
The Contact Management System (CMS) is a simple yet efficient console-based application developed in the C programming language for storing, managing, and retrieving personal contact information. This project demonstrates the use of file handling, structures, and basic CRUD operations (Create, Read, Update, Delete), making it an excellent learning project for beginners in C programming and file-based data management.

The main objective of this system is to provide users with a seamless way to add, view, search, edit, and delete contacts. Each contact typically includes essential details such as Name, Phone Number, Email, and Address. The program stores all records in a local text file (contacts.dat or .txt) to ensure persistence even after the application closes.

🔧 Key Features
✔️ 1. Add New Contact

Allows users to create and save a new contact by entering required details.
The data is validated (e.g., phone number format) and then appended to the file.

✔️ 2. Display All Contacts

Reads the stored file and displays all contact entries in a clean tabular format.
Helps users quickly view their entire directory.

✔️ 3. Search Contact

Users can search for a specific contact using keywords such as:

Name

Phone number

Email

The system scans the stored records and displays the matching contact.

✔️ 4. Edit Existing Contact

Users can update the details of an already saved contact.
The old entry is replaced with the new one while maintaining data structure integrity.

✔️ 5. Delete Contact

Allows removal of a specific contact.
This is done by copying all other entries to a temporary file and replacing the original file.

✔️ 6. Secure File-Based Storage

All contacts are stored in a file using C’s standard file I/O operations (fopen, fwrite, fread, etc.).
This ensures data persistence even if the program is closed.

🛠️ Technical Concepts Used
🗂️ 1. Structures (struct)

Used to group all contact information into one structured data type.

📁 2. File Handling

The program makes heavy use of:

fopen()

fclose()

fread()

fwrite()

fprintf() / fscanf()

This allows permanent storage of contact information.

🔄 3. CRUD Operations

Demonstrates basic data management operations implemented manually using text/binary files.

🧩 4. String Handling

Functions like strcpy(), strcmp(), and input functions (gets, fgets) are used to manipulate text fields.

🧪 5. Input Validation

Simple checks for empty fields or invalid phone numbers ensure accurate data entry.

🧑‍💻 Project Flow

User is presented with a menu-driven interface.

Chooses an option such as Add, View, Search, Edit, or Delete.

Program processes the request using file handling + structures.

Displays result and returns to menu until the user exits.

This makes the system user-friendly and easy to operate.

🎯 Learning Outcomes

By working with this project, a learner gains hands-on experience with:

Procedural programming in C

Data persistence through files

Real-world CRUD operations

Handling structured data

Writing clear, modular code

Working with loops, conditions, and memory concepts

🚀 Use Cases

Personal contact storage

College lab assignments

Mini project for C programming courses

Demonstration of file handling and structure usage

Foundation for more advanced systems (GUI, database-based contact app)

🏁 Conclusion

The Contact Management System in C is a practical, educational project that shows how to build a real-world application using simple tools available in the C language. It combines key concepts like structures, file I/O, loops, and conditionals to create a functional contact directory with persistent storage. Its simplicity, scalability, and educational value make it ideal for beginners and intermediate programmers seeking to strengthen their core C programming skills.
