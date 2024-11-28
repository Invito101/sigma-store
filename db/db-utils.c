#include <stdio.h>
#include <sqlite3.h>
#include "../headers.h"

sqlite3* open_db(void){
    sqlite3 *db;
    int rc = sqlite3_open("db/SigmaStore.db", &db);

    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        close_db(db); // Close the database connection if it was partially opened
        exit(0);
    }

    return db;
}

void close_db(sqlite3 *db){
    sqlite3_close(db);
}

int create_tables(void){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password VARCHAR(110), phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt INT NOT NULL);"

    "CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY, name VARCHAR(300) UNIQUE, price INT, description VARCHAR(1000), category VARCHAR(300), manufacturedBy VARCHAR(300), rating DOUBLE, noOfRatings INT, amountBought INT, createdAt INT NOT NULL);"

    "CREATE TABLE IF NOT EXISTS Orders(id INTEGER PRIMARY KEY, userId INT, createdAt INT NOT NULL, delivered INT DEFAULT 0, FOREIGN KEY (userId) REFERENCES Users(id));"

    "CREATE TABLE IF NOT EXISTS Cart(id INTEGER PRIMARY KEY, quantity INT, userId INT, productId INT, orderId INT DEFAULT NULL, FOREIGN KEY (userId) REFERENCES Users(id), FOREIGN KEY (productId) REFERENCES Products(id), FOREIGN KEY (orderId) REFERENCES Orders(id));";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Failed to create tables: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        close_db(db);
        return -1;
    }

    close_db(db);
    return 0;
}

int init_db(){
    // Books
    create_product("The Great Sumanth", 299, "A classic novel by F. Scott Fitzgerald", "Books", "Pragun Classics");
    create_product("Introduction to Real Analysis", 1500, "Comprehensive guide on analysis", "Books", "Shanti Narayan");
    create_product("Harry Potter and the Philosopher's Stone", 499, "Fantasy novel by J.K. Rowling", "Books", "Bloomsbury");
    create_product("Sapiens: A Brief History of Humankind", 799, "By Yuval Noah Harari", "Books", "Harper Perennial");
    create_product("Atomic Habits", 599, "Practical guide to building good habits", "Books", "Penguin Random House");
    create_product("1984", 399, "Dystopian novel by George Orwell", "Books", "Secker & Warburg");
    create_product("The Catcher in the Rye", 499, "Novel by J.D. Salinger", "Books", "Little, Brown and Company");
    create_product("To Kill a Pig", 349, "Classic novel by Brett Lee", "Books", "J.B. Lippincott & Co.");
    create_product("Pride and Prejudice", 299, "Romantic novel by Jane Austen", "Books", "Modern Library");
    create_product("The Alchemist", 599, "Philosophical novel by Paulo Coelho", "Books", "HarperOne");
    create_product("Becoming", 699, "Memoir by Michelle Obama", "Books", "Crown Publishing Group");
    create_product("Educated", 549, "Memoir by Tara Westover", "Books", "Random House");
    create_product("The Power of Habit", 499, "Self-help book by Charles Duhigg", "Books", "Random House");
    create_product("The Subtle Art of Not Giving a F*ck", 599, "By Mark Manson", "Books", "HarperOne");
    create_product("The Book Thief", 699, "Historical novel by Markus Zusak", "Books", "Knopf");
    create_product("The Road", 399, "Post-apocalyptic novel by Cormac McCarthy", "Books", "Knopf");
    create_product("Meditations", 299, "Philosophical writings by Marcus Aurelius", "Books", "Penguin Classics");
    create_product("Dune", 499, "Sci-fi novel by Frank Herbert", "Books", "Ace Books");
    create_product("Think and Grow Rich", 349, "Self-help classic by Napoleon Hill", "Books", "The Ralston Society");
    create_product("Crime and Punishment", 699, "Novel by Fyodor Dostoevsky", "Books", "Penguin Classics");

    // Electronics
    create_product("Wireless Headphones", 1999, "Bluetooth over-ear headphones", "Electronics", "Sony");
    create_product("Smartphone", 24999, "Android device with 128GB storage", "Electronics", "Samsung");
    create_product("Laptop", 54999, "15-inch laptop with 8GB RAM", "Electronics", "Dell");
    create_product("Smartwatch", 9999, "Fitness tracker with heart rate monitoring", "Electronics", "Apple");
    create_product("Bluetooth Speaker", 3499, "Portable speaker with deep bass", "Electronics", "JBL");
    create_product("LED TV", 24999, "43-inch smart LED TV", "Electronics", "Samsung");
    create_product("Gaming Console", 39999, "Next-gen gaming console", "Electronics", "Sony");
    create_product("Tablet", 15999, "10-inch tablet with 64GB storage", "Electronics", "Lenovo");
    create_product("Action Camera", 19999, "4K waterproof camera", "Electronics", "GoPro");
    create_product("External Hard Drive", 5999, "1TB USB 3.0 drive", "Electronics", "Seagate");
    create_product("Wi-Fi Router", 2999, "Dual-band wireless router", "Electronics", "TP-Link");
    create_product("Desktop Monitor", 11999, "27-inch full HD monitor", "Electronics", "LG");
    create_product("Keyboard", 1499, "Mechanical keyboard with RGB lighting", "Electronics", "Corsair");
    create_product("Mouse", 999, "Wireless ergonomic mouse", "Electronics", "Logitech");
    create_product("VR Headset", 34999, "Virtual reality headset", "Electronics", "Meta");
    create_product("Power Bank", 1999, "10000mAh portable charger", "Electronics", "Xiaomi");
    create_product("Smart Bulb", 1499, "Wi-Fi enabled LED bulb", "Electronics", "Philips");
    create_product("Projector", 24999, "Full HD home projector", "Electronics", "Epson");
    create_product("Noise Cancelling Headphones", 29999, "Over-ear headphones", "Electronics", "Bose");
    create_product("Portable SSD", 9999, "500GB high-speed SSD", "Electronics", "SanDisk");

    // Fashion
    create_product("Leather Jacket", 3999, "Men's black leather jacket", "Fashion", "Zara");
    create_product("Sneakers", 2499, "Comfortable running shoes", "Fashion", "Nike");
    create_product("Wrist Watch", 1499, "Stylish analog watch", "Fashion", "Casio");
    create_product("Sunglasses", 999, "UV-protective polarized lenses", "Fashion", "Ray-Ban");
    create_product("Denim Jeans", 1999, "Blue slim-fit jeans", "Fashion", "Levi's");
    create_product("T-shirt", 799, "Cotton crew neck t-shirt", "Fashion", "H&M");
    create_product("Dress", 1999, "Floral print summer dress", "Fashion", "Forever 21");
    create_product("Formal Shoes", 3499, "Men's leather formal shoes", "Fashion", "Bata");
    create_product("Handbag", 2499, "Trendy women's tote bag", "Fashion", "Coach");
    create_product("Hat", 599, "Classic wide-brim hat", "Fashion", "Hats Unlimited");
    create_product("Scarf", 999, "Wool blend winter scarf", "Fashion", "Calvin Klein");
    create_product("Sportswear Set", 2499, "Workout leggings and top", "Fashion", "Adidas");
    create_product("Polo Shirt", 1299, "Men's cotton polo shirt", "Fashion", "Lacoste");
    create_product("Jacket", 4999, "Women's padded winter jacket", "Fashion", "The North Face");
    create_product("Backpack", 2999, "Stylish laptop backpack", "Fashion", "Fjällräven");
    create_product("Casual Shorts", 1299, "Men's cotton shorts", "Fashion", "Levi's");
    create_product("Socks", 299, "Pack of 3 ankle-length socks", "Fashion", "Puma");
    create_product("Belt", 699, "Leather belt with metal buckle", "Fashion", "Tommy Hilfiger");
    create_product("Cap", 499, "Adjustable baseball cap", "Fashion", "Nike");
    create_product("Earrings", 1499, "Gold-plated drop earrings", "Fashion", "Zara");


    // Sports and Fitness
    create_product("Yoga Mat", 899, "Non-slip, lightweight yoga mat", "Sports and Fitness", "Reebok");
    create_product("Treadmill", 24999, "Electric treadmill for cardio workouts", "Sports and Fitness", "PowerMax");
    create_product("Dumbbell Set", 2999, "Adjustable weight dumbbell set", "Sports and Fitness", "Bowflex");
    create_product("Football", 999, "FIFA approved match ball", "Sports and Fitness", "Adidas");
    create_product("Resistance Bands", 499, "Set of 5 resistance bands", "Sports and Fitness", "Fit Simplify");
    create_product("Cricket Bat", 1999, "Grade 1 English Willow bat", "Sports and Fitness", "SG");
    create_product("Running Shoes", 3999, "High-performance running shoes", "Sports and Fitness", "Asics");
    create_product("Fitness Tracker", 4999, "Wearable fitness band", "Sports and Fitness", "Fitbit");
    create_product("Skipping Rope", 499, "Adjustable speed rope", "Sports and Fitness", "Nike");
    create_product("Basketball", 1499, "Official size basketball", "Sports and Fitness", "Spalding");
    create_product("Swimming Goggles", 699, "Anti-fog swimming goggles", "Sports and Fitness", "Speedo");
    create_product("Yoga Block", 599, "Foam yoga block for support", "Sports and Fitness", "Manduka");
    create_product("Punching Bag", 3999, "Heavy-duty punching bag", "Sports and Fitness", "Everlast");
    create_product("Cycling Helmet", 1999, "Protective bike helmet", "Sports and Fitness", "Giro");
    create_product("Tennis Racket", 2499, "Lightweight aluminum racket", "Sports and Fitness", "Wilson");
    create_product("Elliptical Trainer", 29999, "Home gym cardio machine", "Sports and Fitness", "Sole Fitness");
    create_product("Soccer Jersey", 999, "Official team jersey", "Sports and Fitness", "Adidas");
    create_product("Foam Roller", 899, "Muscle recovery roller", "Sports and Fitness", "TriggerPoint");
    create_product("Climbing Rope", 2999, "Durable outdoor rope", "Sports and Fitness", "Black Diamond");
    create_product("Hiking Backpack", 4499, "50L trekking backpack", "Sports and Fitness", "Osprey");

    // Games
    create_product("Chess Set", 999, "Wooden chess board with pieces", "Games", "Handcrafted Creations");
    create_product("Playing Cards", 199, "Standard deck of 52 cards", "Games", "Bicycle");
    create_product("Board Game - Monopoly", 1499, "Classic property trading game", "Games", "Hasbro");
    create_product("Jigsaw Puzzle", 499, "1000-piece nature scenery puzzle", "Games", "Ravensburger");
    create_product("Video Game - Elden Ring", 3999, "Action role-playing game", "Games", "Bandai Namco");
    create_product("Rubik's Cube", 499, "3x3 classic cube puzzle", "Games", "Rubik's");
    create_product("Puzzle Cube Set", 899, "Set of 5 unique cubes", "Games", "Gan");
    create_product("UNO Cards", 399, "Fun card game for all ages", "Games", "Mattel");
    create_product("Scrabble", 1499, "Word-building board game", "Games", "Hasbro");
    create_product("Clue", 1299, "Mystery solving board game", "Games", "Hasbro");
    create_product("Snakes and Ladders", 499, "Classic board game", "Games", "Funskool");
    create_product("Dart Board", 1999, "Professional dartboard set", "Games", "Winmau");
    create_product("Toy Train Set", 2999, "Electric toy train set", "Games", "Fisher-Price");
    create_product("Racing Game", 3999, "Car racing video game", "Games", "Electronic Arts");
    create_product("Role-Playing Dice Set", 999, "7-dice set for tabletop RPGs", "Games", "Chessex");
    create_product("Beyblade", 799, "Spinning battle top", "Games", "Takara Tomy");
    create_product("Model Building Kit", 1999, "Build and paint model set", "Games", "Tamiya");
    create_product("Magic: The Gathering Cards", 2999, "Fantasy card deck", "Games", "Wizards of the Coast");
    create_product("Catan", 2499, "Strategy board game", "Games", "Catan Studio");
    create_product("Laser Tag Guns", 4999, "Indoor laser tag set", "Games", "Nerf");


    // Edibles
    create_product("Dark Chocolate", 299, "Rich and creamy chocolate", "Edibles", "Lindt");
    create_product("Organic Honey", 499, "Pure and natural honey", "Edibles", "Dabur");
    create_product("Green Tea", 199, "20 sachets of premium green tea", "Edibles", "Lipton");
    create_product("Trail Mix", 299, "Healthy nuts and dried fruits", "Edibles", "Happilo");
    create_product("Instant Coffee", 349, "Premium freeze-dried coffee", "Edibles", "Nescafé");
    create_product("Peanut Butter", 399, "Creamy peanut butter with no added sugar", "Edibles", "Pintola");
    create_product("Almond Milk", 299, "Dairy-free almond milk", "Edibles", "Silk");
    create_product("Multigrain Biscuits", 149, "Fiber-rich multigrain biscuits", "Edibles", "Britannia");
    create_product("Energy Bars", 299, "Pack of 6 protein-packed energy bars", "Edibles", "Kind");
    create_product("Oats", 249, "Whole grain rolled oats for a healthy breakfast", "Edibles", "Quaker");
    create_product("Herbal Tea", 349, "Calming herbal tea with chamomile", "Edibles", "Twinings");
    create_product("Pasta Sauce", 499, "Italian-style tomato and basil sauce", "Edibles", "Barilla");
    create_product("Instant Noodles", 49, "Classic masala-flavored noodles", "Edibles", "Maggi");
    create_product("Coconut Water", 199, "100% natural tender coconut water", "Edibles", "Cocojal");
    create_product("Gourmet Popcorn", 399, "Caramel and cheese flavored popcorn", "Edibles", "Act II");

    // Home and Kitchen
    create_product("Vacuum Cleaner", 6999, "Bagless upright vacuum cleaner", "Home and Kitchen", "Dyson");
    create_product("Microwave Oven", 8499, "30L convection microwave", "Home and Kitchen", "LG");
    create_product("Non-Stick Cookware Set", 2999, "5-piece cookware set", "Home and Kitchen", "Prestige");
    create_product("Air Purifier", 12999, "HEPA filter air purifier", "Home and Kitchen", "Philips");
    create_product("Electric Kettle", 1299, "1.5L stainless steel kettle", "Home and Kitchen", "Borosil");
    create_product("Dishwasher", 24999, "Fully automatic dishwasher", "Home and Kitchen", "Bosch");
    create_product("Blender", 2599, "High-speed blender for smoothies", "Home and Kitchen", "Philips");
    create_product("Refrigerator", 17999, "Double door refrigerator with inverter technology", "Home and Kitchen", "Samsung");
    create_product("Coffee Maker", 3999, "Espresso machine with milk frother", "Home and Kitchen", "Breville");
    create_product("Induction Cooktop", 3999, "Portable induction cooktop with 3 heat settings", "Home and Kitchen", "Preethi");
    create_product("Toaster", 1499, "2-slice toaster with browning control", "Home and Kitchen", "Crompton");
    create_product("Electric Pressure Cooker", 6999, "Multi-function electric pressure cooker", "Home and Kitchen", "Prestige");
    create_product("Water Purifier", 4999, "RO + UV water purifier", "Home and Kitchen", "Kent");
    create_product("Iron", 1999, "Steam iron with auto shut-off", "Home and Kitchen", "Philips");
    create_product("Cordless Vacuum Cleaner", 8499, "Lightweight cordless vacuum with long battery life", "Home and Kitchen", "Dyson");

    return 0;
}