import sqlite3
from faker import Faker
import random
import time

faker = Faker()

conn = sqlite3.connect('../db/SigmaStore.db')
cursor = conn.cursor()

def generate_tables():
    cursor.execute("CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password VARCHAR(110), phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt INT NOT NULL);CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY, name VARCHAR(300) UNIQUE, price INT, description VARCHAR(1000), category VARCHAR(300), manufacturedBy VARCHAR(300), rating DOUBLE, noOfRatings INT, amountBought INT, createdAt INT NOT NULL);CREATE TABLE IF NOT EXISTS Orders(id INTEGER PRIMARY KEY, userId INT, createdAt INT NOT NULL, FOREIGN KEY (userId) REFERENCES Users(id));CREATE TABLE IF NOT EXISTS Cart(id INTEGER PRIMARY KEY, quantity INT, userId INT, productId INT, ordered INT DEFAULT 0, orderId INT DEFAULT NULL, FOREIGN KEY (userId) REFERENCES Users(id), FOREIGN KEY (productId) REFERENCES Products(id), FOREIGN KEY (orderId) REFERENCES Orders(id));")

def generate_users(num_users):
    for i in range(1, num_users + 1):
        name = faker.name()
        email = faker.unique.email()
        role = random.choice(['user', 'admin'])
        password = faker.name()
        phone = faker.unique.msisdn()[:10]
        address = faker.address().replace("\n", ", ")
        pincode = random.randint(100000, 999999)
        state = faker.state()
        money = random.randint(1000, 50000)
        created_at = int(time.time())
        
        cursor.execute("""INSERT INTO Users (id, name, email, role, password, phoneNumber, address, pincode, state, money, createdAt) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""", (i, name, email, role, password, phone, address, pincode, state, money, created_at))

def generate_products(num_products):
    for i in range(1, num_products + 1):
        name = faker.unique.word().capitalize() + " " + random.choice(['Laptop', 'Smartphone', 'Headphones', 'Table', 'Shoes'])
        price = random.randint(500, 100000)
        description = faker.text(max_nb_chars=200)
        category = random.choice(['Electronics', 'Furniture', 'Clothing', 'Accessories', 'Appliances'])
        manufactured_by = faker.company()
        rating = round(random.uniform(1, 5), 1)
        no_of_ratings = random.randint(10, 1000)
        amount_bought = random.randint(0, 500)
        created_at = int(time.time())
        
        cursor.execute("""
            INSERT INTO Products (id, name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        """, (i, name, price, description, category, manufactured_by, rating, no_of_ratings, amount_bought, created_at))

def generate_orders(num_orders, num_users):
    for i in range(1, num_orders + 1):
        user_id = random.randint(1, num_users)
        created_at = int(time.time())
        
        cursor.execute("""
            INSERT INTO Orders (id, userId, createdAt)
            VALUES (?, ?, ?)
        """, (i, user_id, created_at))

def generate_cart(num_cart_items, num_users, num_products, num_orders):
    for i in range(1, num_cart_items + 1):
        quantity = random.randint(1, 10)
        user_id = random.randint(1, num_users)
        product_id = random.randint(1, num_products)
        ordered = random.choice([0, 1])
        order_id = random.randint(1, num_orders) if ordered else None
        
        cursor.execute("""
            INSERT INTO Cart (id, quantity, userId, productId, ordered, orderId)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (i, quantity, user_id, product_id, ordered, order_id))

num_users = 100
num_products = 200
num_orders = 150
num_cart_items = 300

generate_tables()
generate_users(num_users)
generate_products(num_products)
generate_orders(num_orders, num_users)
generate_cart(num_cart_items, num_users, num_products, num_orders)

conn.commit()
conn.close()
