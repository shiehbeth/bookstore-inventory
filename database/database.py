import pandas as pd
from sqlalchemy import create_engine

# Replace with your MySQL credentials
username = 'root'
password = ''
host = '127.0.0.1'  # localhost' or '127.0.0.1'
port = '3306'  # default MySQL port
database = 'BOOKDB'
table_name = 'books'
table_name2 = 'rating'

# Create the connection string
connection_string = f'mysql+mysqlconnector://{username}:{password}@{host}:{port}/{database}'

# Create the database connection
engine = create_engine(connection_string)

# Replace 'your_file.csv' with the path to your input CSV file
csv_file_path = 'books_data/new_books.csv'
csv_rating_path = 'books_data/new_ratings.csv'

# Read the CSV file into a DataFrame
# df = pd.read_csv(csv_file_path)
df = pd.read_csv(csv_rating_path)
# third_column_data = df.iloc[:, 2].tolist()
print(df.head())

# Print the third column data
# print(third_column_data)
# Write the DataFrame to the MySQL table
df.to_sql(name=table_name2, con=engine, if_exists='append', index=False)
