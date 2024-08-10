# Beth and Shirley's Bookstore Management System

## Description:
This project creates a program that manages books in a bookstore as well as books in a user's personal collection. This project takes in books from a dataset on Kaggle, and uses a MySQL database to store the data. Using the command line, the user can search for books and/or add books to their personal collection.

- Features:
Included are features for searching for a book by title, author, or ISBN number. The user can search for books within the database,
or they can search and sort books within their own collection by title, author, or ISBN number. The user's own collections include a user's top 5 rated books (organized based on rating from high to low), reading list (contains books that a user would like to read), and history books (contains books that a user has read in the past). The user can add books to their reading list, and move books from their reading list to their history books after they have finished reading.

- Technologies Used:
C, MySQL, Python.

- Challenges:
Because of the large volume of data (250,000+ books) provided in the dataset, we ran into challenges of ingesting all of the data and instead chose to handle a smaller subset of the book data. We also have not implemented creating and storing multiple users yet, but have demonstrated functionality with one "fake user".

- Folder Structure:
Below is the folder structure and general organization of our project.

```
.
bookstore_inventory/
├── database/
│   ├── books_data
│   |   ├── books.csv
│   |   ├── new_books.csv
│   |   ├── new_ratings.csv
│   |   ├── ratings.csv
│   |   ├── user.info.txt
│   |   ├── users.csv
|   ├── clean.py
|   ├── database.py
|   ├── mysql_connection_test.py
├── include/
│   ├── hashset.h
│   ├── header.h
│   ├── search.h
│   ├── user.h
├── src/
│   ├── book.c
│   ├── hashset.c
│   ├── inventory.c
│   ├── LinkedList.c
│   ├── main.c
│   ├── markAsRead.c
│   ├── retrieveData.c
│   ├── searchSortPersonal.c
├── Makefile
└── README.md
```

## How to Use:
Compile using Makefile, and run the book file. Use the command line to input one of four commands: Add, Show, Search, or Done.
    - Add: Finds a book in the inventory and adds to the user's collection
    - Show: Displays books in the users collections
    - Search: Provides searching functionality
        - Enter 1 to search in the inventory
        - Enter 2 to search in the user's personal collection
            - Terminal will further prompt for keyword to search by (author, title, ISBN)
    - Done: Exits the book management system

## Contact:
- Beth Shieh - shieh.b@northeastern.edu
- Shirley Xiaoxue Fang - fang.xiaox@northeastern.edu
- Project Link - https://github.com/shiehbeth/bookstore-inventory
