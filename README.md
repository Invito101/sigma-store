# Sigma Store - eCommerce System (ECS)

## Overview

The eCommerce System (ECS) is a terminal-based application designed to manage product listings, customer orders, and product statistics. It provides two distinct interfaces: one for customers to place orders and another for admins to manage the products and view statistics. The system also stores product and order data in an SQLite database for easy access and management.

## Key Features

1. **User Authentication and Authorization**

    - **Authentication Display**: Secure Login and Registration System using SQLite.
    - **Password Storage**: Passwords are encrypted using Caesar Cipher for secure storage.

2. **Customer Interface**

    - **Product Browsing**: View available products with details like name, price, and description.
    - **Dynamic Cart Management**: Add items to a cart, view total cost, and complete the order process. Each user's cart is managed with a linked list, storing products and their quantities.
    - **Order History**: View their order history and rate a product out of five.

3. **Admin Interface**:

    - **Product Management**: Add, edit, modify or remove products from the inventory.
    - **Order Management**: View, update, and delete orders as necessary.

4. **Data Storage with Structs**

    - **C Structs**: Core application entities like users, products, and orders are represented using C structs, providing an organized way to store and manipulate data.

5. **Data Persistence**
    - **SQLite**: All user data, product details, and order histories are stored and retrieved from a SQLite database.

## Technologies Used

1. **C**: Core programming language for implementing functionalities.
2. **SQLite**: Database for persistent data storage.
3. **ncurses**: Library for creating a text-based user interface.
4. **Makefile**: For simplifying the build process.

## Installation

### Prerequisites

Before running the application, ensure the following dependencies are installed:

### SQLite3 Installation

For database operations, SQLite3 is required. Install it using the following commands:

```bash
sudo apt-get install libsqlite3-dev
```

```bash
sudo apt install sqlite3
```

### ncurses Installation

The application uses ncurses for the text-based user interface. Follow these steps to install ncurses:

1. Download the Stable Release Source from this [link](https://invisible-island.net/ncurses/ncurses.html#download_ncurses).

2. Extract and build ncurses: (Replace `<version>` with the version you downloaded)

    ```bash
     tar zxvf ncurses<version>.tar.gz  # Unzip and untar the archive
     cd ncurses<version>               # Navigate to the extracted directory
     ./configure                       # Configure the build for your environment
     make                              # Build the package
     sudo -i                           # Switch to root user
    ```

3. Navigate to the extracted ncurses folder as root and install:

    ```bash
     make install
    ```

### Steps to Install and Run

1. Clone the repository:
    ```bash
    git clone https://github.com/Invito101/sigma-store.git
    ```
2. Move into the sigma-store directory:
    ```bash
    cd sigma-store
    ```
3. Make the build script executable:
    ```bash
     chmod +x build_clean_run.sh
    ```
4. Compile and run the project using the provided build script:
    ```bash
     ./build_clean_run.sh
    ```

## How to Use

Once the project is installed and the dependencies are configured, you can use the application as follows:

1. **Start the Application**

    - Run the build script:
        ```bash
        ./build_clean_run.sh
        ```
    - This will clean old builds, compile the project, and launch the application.

2. **Registration and Login**
    - When the application starts, you will be prompted to register or log in with your email address:
        - If your email ends with `@sigmastore.in`, the system will recognize you as an **admin** and grant you admin access immediately.
        - If your email does not end with `@sigmastore.in`, the system will register you as a **customer** and provide access to customer features only.
3. **Customer Features**
    - As a customer, you can:
        - Browse available products.
        - Add products to your cart.
        - View your cart.
        - Place orders securely.
        - View your order history.
        - Rate a product.
4. **Admin Features**
    - As an admin, you can:
        - Manage the product inventory (add, edit, or remove products).
        - View and manage customer orders.
        - Access additional administrative tools and statistics.

## Contributors

1. [Akshay K M](https://github.com/Akshay-K-M)
2. [Anurag Rao U](https://github.com/Invito101)
3. [H Sanjay](https://github.com/Bit-by-bit-coder)
4. [K Sai Amith](https://github.com/Dictator-00)
5. [S Arjun Sai](https://github.com/broskitos)
6. [Sumanth Y M](https://github.com/Sumanth-YM)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
