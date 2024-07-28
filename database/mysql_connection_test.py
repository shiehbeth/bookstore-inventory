import mysql.connector
from mysql.connector import Error


def describe_table(host_name, user_name, user_password, db_name, table_name):
    """ Function to describe a table in MySQL database """
    try:
        # Connection to the database
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            password=user_password,
            database=db_name
        )

        if connection.is_connected():
            # Create a cursor to perform database operations
            cursor = connection.cursor()
            # Executing a SQL query to describe a table
            cursor.execute(f"DESCRIBE {table_name}")
            # Fetch result
            rows = cursor.fetchall()
            print(f"Description of the table '{table_name}':")
            for row in rows:
                print(row)

    except Error as e:
        print("Error while connecting to MySQL", e)
    
    finally:
        # Closing database connection.
        if connection.is_connected():
            cursor.close()
            connection.close()
            print("MySQL connection is closed")


# Specify your own database credentials
host_name = "127.0.0.1"
user_name = "root"
user_password = "Shirley*!(*!!"
db_name = "BOOKDB"
table_name = "BOOK_INFO"

# Function call to describe a table
describe_table(host_name, user_name, user_password, db_name, table_name)
