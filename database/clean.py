import pandas as pd

input_file_path = 'books_data/books.csv'
output_file_path = 'books_data/new_books.csv'


def save_books_to_database():
    expected_dtypes = {
        'ISBN': str,
        'Book_Title': str,
        'Book_Author': str,
        'Year_Of_Publication': int,  # Must be an integer
        'Publisher': str,
    }
    df = pd.read_csv(input_file_path, delimiter=',', low_memory=False)
    df = df.iloc[:, :-6]
    for column, dtype in expected_dtypes.items():
        # Attempt to convert data types
        try:
            df[column] = df[column].astype(dtype)
        except ValueError:
            # If type conversion fails, filter out those rows
            df = df[pd.to_numeric(df[column], errors='coerce').notnull()] if dtype == int else df
    # Save the modified DataFrame to a new CSV file
    sub_df = df.head(20000)
    # df.to_csv(output_file_path, index=False)
    sub_df.to_csv(output_file_path, index=False)


#user_id,ISBN,book_rating
# user_id INT,     ISBN INT,     book_rating INT
def save_user_to_database():
    input_rating_path = 'books_data/ratings.csv'
    output_rating_path = 'books_data/new_ratings.csv'
    expected_dtypes = {
        'user_id': int,
        'ISBN': str,
        'book_rating': int,
    }
    df = pd.read_csv(input_rating_path, delimiter=',')
    # df = df.iloc[:, :-6]
    for column, dtype in expected_dtypes.items():
        # Attempt to convert data types
        try:
            df[column] = df[column].astype(dtype)
        except ValueError:
            # If type conversion fails, filter out those rows
            df = df[pd.to_numeric(df[column], errors='coerce').notnull()] if dtype == int else df
    # Save the modified DataFrame to a new CSV file
    sub_df = df.head(20000)
    # df.to_csv(output_file_path, index=False)
    sub_df.to_csv(output_rating_path, index=False)


def check_data():
    df = pd.read_csv(output_file_path, decimal=',')
    print(df.head())


# target: user
def main():
    # save_books_to_database()
    save_user_to_database()
    # check_data()


if __name__ == '__main__':
    main()


# Write the CSV file with the desired encoding
# df.to_csv(output_file_path, index=False, encoding=desired_encoding)