CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password VARCHAR(110), phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt INT NOT NULL);

CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY, name VARCHAR(300) UNIQUE, price INT, description VARCHAR(1000), category VARCHAR(300), manufacturedBy VARCHAR(300), rating DOUBLE, noOfRatings INT, amountBought INT, createdAt INT NOT NULL);

CREATE TABLE IF NOT EXISTS Orders(id INTEGER PRIMARY KEY, userId INT, createdAt INT NOT NULL, delivered INT DEFAULT 0, FOREIGN KEY (userId) REFERENCES Users(id));

CREATE TABLE IF NOT EXISTS Cart(id INTEGER PRIMARY KEY, quantity INT, userId INT, productId INT, orderId INT DEFAULT NULL, FOREIGN KEY (userId) REFERENCES Users(id), FOREIGN KEY (productId) REFERENCES Products(id), FOREIGN KEY (orderId) REFERENCES Orders(id));


-- Books
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES 
    ("The Great Sumanth", 299, "A classic novel by F. Scott Fitzgerald", "Books", "Pragun Classics", 4.65, 637, 1243, 1732804967),
    ("Introduction to Real Analysis", 1500, "Comprehensive guide on analysis", "Books", "Shanti Narayan", 4.8, 129, 342, 1732805967),
    ("Harry Potter and the Philosopher's Stone", 499, "Fantasy novel by J.K. Rowling", "Books", "Bloomsbury", 4.9, 763, 1542, 1732806967),
    ("Sapiens: A Brief History of Humankind", 799, "By Yuval Noah Harari", "Books", "Harper Perennial", 4.7, 1167, 1834, 1732807967),
    ("Atomic Habits", 599, "Practical guide to building good habits", "Books", "Penguin Random House", 4.85, 926, 1376, 1732808967),
    ("1984", 399, "Dystopian novel by George Orwell", "Books", "Secker & Warburg", 4.9, 487, 1023, 1732809967),
    ("The Catcher in the Rye", 499, "Novel by J.D. Salinger", "Books", "Little, Brown and Company", 4.6, 578, 967, 1732810967),
    ("To Kill a Pig", 349, "Classic novel by Brett Lee", "Books", "J.B. Lippincott & Co.", 4.7, 276, 612, 1732811967),
    ("Pride and Prejudice", 299, "Romantic novel by Jane Austen", "Books", "Modern Library", 4.8, 782, 1237, 1732812967),
    ("The Alchemist", 599, "Philosophical novel by Paulo Coelho", "Books", "HarperOne", 4.85, 673, 1456, 1732813967),
    ("Becoming", 699, "Memoir by Michelle Obama", "Books", "Crown Publishing Group", 4.9, 387, 823, 1732814967),
    ("Educated", 549, "Memoir by Tara Westover", "Books", "Random House", 4.8, 436, 715, 1732815967),
    ("The Power of Habit", 499, "Self-help book by Charles Duhigg", "Books", "Random House", 4.75, 487, 932, 1732816967),
    ("The Subtle Art of Not Giving a F*ck", 599, "By Mark Manson", "Books", "HarperOne", 4.6, 339, 725, 1732817967),
    ("The Book Thief", 699, "Historical novel by Markus Zusak", "Books", "Knopf", 4.9, 876, 1534, 1732818967),
    ("The Road", 399, "Post-apocalyptic novel by Cormac McCarthy", "Books", "Knopf", 4.65, 187, 412, 1732819967),
    ("Meditations", 299, "Philosophical writings by Marcus Aurelius", "Books", "Penguin Classics", 4.7, 136, 312, 1732820967),
    ("Dune", 499, "Sci-fi novel by Frank Herbert", "Books", "Ace Books", 4.85, 967, 2043, 1732821967),
    ("Think and Grow Rich", 349, "Self-help classic by Napoleon Hill", "Books", "The Ralston Society", 4.75, 389, 723, 1732822967),
    ("Crime and Punishment", 699, "Novel by Fyodor Dostoevsky", "Books", "Penguin Classics", 4.9, 776, 1237, 1732823967);

-- Electronics
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Wireless Headphones", 1999, "Bluetooth over-ear headphones", "Electronics", "Sony", 4.6, 436, 824, 1732804967),
    ("Smartphone", 24999, "Android device with 128GB storage", "Electronics", "Samsung", 4.8, 1456, 2576, 1732805967),
    ("Laptop", 54999, "15-inch laptop with 8GB RAM", "Electronics", "Dell", 4.7, 776, 1342, 1732806967),
    ("Smartwatch", 9999, "Fitness tracker with heart rate monitoring", "Electronics", "Apple", 4.9, 1167, 2056, 1732807967),
    ("Bluetooth Speaker", 3499, "Portable speaker with deep bass", "Electronics", "JBL", 4.75, 678, 1132, 1732808967),
    ("LED TV", 24999, "43-inch smart LED TV", "Electronics", "Samsung", 4.8, 967, 1645, 1732809967),
    ("Gaming Console", 39999, "Next-gen gaming console", "Electronics", "Sony", 4.9, 582, 927, 1732810967),
    ("Tablet", 15999, "10-inch tablet with 64GB storage", "Electronics", "Lenovo", 4.6, 436, 768, 1732811967),
    ("Action Camera", 19999, "4K waterproof camera", "Electronics", "GoPro", 4.85, 291, 617, 1732812967),
    ("External Hard Drive", 5999, "1TB USB 3.0 drive", "Electronics", "Seagate", 4.7, 194, 412, 1732813967),
    ("Wi-Fi Router", 2999, "Dual-band wireless router", "Electronics", "TP-Link", 4.75, 387, 723, 1732814967),
    ("Desktop Monitor", 11999, "27-inch full HD monitor", "Electronics", "LG", 4.8, 291, 512, 1732815967),
    ("Keyboard", 1499, "Mechanical keyboard with RGB lighting", "Electronics", "Corsair", 4.6, 582, 927, 1732816967),
    ("Mouse", 999, "Wireless ergonomic mouse", "Electronics", "Logitech", 4.7, 776, 1237, 1732817967),
    ("VR Headset", 34999, "Virtual reality headset", "Electronics", "Meta", 4.85, 387, 612, 1732818967),
    ("Power Bank", 1999, "10000mAh portable charger", "Electronics", "Xiaomi", 4.7, 967, 1534, 1732819967),
    ("Smart Bulb", 1499, "Wi-Fi enabled LED bulb", "Electronics", "Philips", 4.65, 1167, 1845, 1732820967),
    ("Projector", 24999, "Full HD home projector", "Electronics", "Epson", 4.8, 678, 1132, 1732821967),
    ("Noise Cancelling Headphones", 29999, "Over-ear headphones", "Electronics", "Bose", 4.9, 291, 612, 1732822967),
    ("Portable SSD", 9999, "500GB high-speed SSD", "Electronics", "SanDisk", 4.75, 387, 723, 1732823967);

-- Fashion
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Leather Jacket", 3999, "Men's black leather jacket", "Fashion", "Zara", 4.7, 298, 499, 1732824967),
    ("Sneakers", 2499, "Comfortable running shoes", "Fashion", "Nike", 4.8, 798, 1197, 1732825967),
    ("Wrist Watch", 1499, "Stylish analog watch", "Fashion", "Casio", 4.6, 497, 798, 1732826967),
    ("Sunglasses", 999, "UV-protective polarized lenses", "Fashion", "Ray-Ban", 4.7, 398, 690, 1732827967),
    ("Denim Jeans", 1999, "Blue slim-fit jeans", "Fashion", "Levi's", 4.8, 999, 1498, 1732828967),
    ("T-shirt", 799, "Cotton crew neck t-shirt", "Fashion", "H&M", 4.65, 598, 898, 1732829967),
    ("Dress", 1999, "Floral print summer dress", "Fashion", "Forever 21", 4.7, 698, 1098, 1732830967),
    ("Formal Shoes", 3499, "Men's leather formal shoes", "Fashion", "Bata", 4.75, 299, 598, 1732831967),
    ("Handbag", 2499, "Trendy women's tote bag", "Fashion", "Coach", 4.8, 499, 899, 1732832967),
    ("Hat", 599, "Classic wide-brim hat", "Fashion", "Hats Unlimited", 4.6, 398, 648, 1732833967),
    ("Scarf", 999, "Wool blend winter scarf", "Fashion", "Calvin Klein", 4.7, 199, 399, 1732834967),
    ("Sportswear Set", 2499, "Workout leggings and top", "Fashion", "Adidas", 4.85, 299, 499, 1732835967),
    ("Polo Shirt", 1299, "Men's cotton polo shirt", "Fashion", "Lacoste", 4.65, 399, 649, 1732836967),
    ("Jacket", 4999, "Women's padded winter jacket", "Fashion", "The North Face", 4.9, 299, 499, 1732837967),
    ("Backpack", 2999, "Stylish laptop backpack", "Fashion", "Fjällräven", 4.8, 499, 799, 1732838967),
    ("Casual Shorts", 1299, "Men's cotton shorts", "Fashion", "Levi's", 4.7, 299, 499, 1732839967),
    ("Socks", 299, "Pack of 3 ankle-length socks", "Fashion", "Puma", 4.65, 798, 1198, 1732840967),
    ("Belt", 699, "Leather belt with metal buckle", "Fashion", "Tommy Hilfiger", 4.75, 399, 698, 1732841967),
    ("Cap", 499, "Adjustable baseball cap", "Fashion", "Nike", 4.7, 598, 898, 1732842967),
    ("Earrings", 1499, "Gold-plated drop earrings", "Fashion", "Zara", 4.85, 299, 499, 1732843967);

-- Sports and Fitness
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Yoga Mat", 899, "Non-slip, lightweight yoga mat", "Sports and Fitness", "Reebok", 4.7, 523, 801, 1732844967),
    ("Treadmill", 24999, "Electric treadmill for cardio workouts", "Sports and Fitness", "PowerMax", 4.8, 319, 512, 1732845967),
    ("Dumbbell Set", 2999, "Adjustable weight dumbbell set", "Sports and Fitness", "Bowflex", 4.75, 438, 691, 1732846967),
    ("Football", 999, "FIFA approved match ball", "Sports and Fitness", "Adidas", 4.8, 618, 901, 1732847967),
    ("Resistance Bands", 499, "Set of 5 resistance bands", "Sports and Fitness", "Fit Simplify", 4.7, 312, 524, 1732848967),
    ("Cricket Bat", 1999, "Grade 1 English Willow bat", "Sports and Fitness", "SG", 4.6, 221, 414, 1732849967),
    ("Running Shoes", 3999, "High-performance running shoes", "Sports and Fitness", "Asics", 4.8, 723, 1014, 1732850967),
    ("Fitness Tracker", 4999, "Wearable fitness band", "Sports and Fitness", "Fitbit", 4.85, 507, 712, 1732851967),
    ("Skipping Rope", 499, "Adjustable speed rope", "Sports and Fitness", "Nike", 4.7, 412, 621, 1732852967),
    ("Basketball", 1499, "Official size basketball", "Sports and Fitness", "Spalding", 4.75, 634, 918, 1732853967),
    ("Swimming Goggles", 699, "Anti-fog swimming goggles", "Sports and Fitness", "Speedo", 4.6, 497, 708, 1732854967),
    ("Yoga Block", 599, "Foam yoga block for support", "Sports and Fitness", "Manduka", 4.7, 321, 534, 1732855967),
    ("Punching Bag", 3999, "Heavy-duty punching bag", "Sports and Fitness", "Everlast", 4.8, 442, 693, 1732856967),
    ("Cycling Helmet", 1999, "Protective bike helmet", "Sports and Fitness", "Giro", 4.7, 517, 734, 1732857967),
    ("Tennis Racket", 2499, "Lightweight aluminum racket", "Sports and Fitness", "Wilson", 4.75, 437, 609, 1732858967),
    ("Elliptical Trainer", 29999, "Home gym cardio machine", "Sports and Fitness", "Sole Fitness", 4.85, 211, 396, 1732859967),
    ("Soccer Jersey", 999, "Official team jersey", "Sports and Fitness", "Adidas", 4.6, 734, 1002, 1732860967),
    ("Foam Roller", 899, "Muscle recovery roller", "Sports and Fitness", "TriggerPoint", 4.7, 333, 502, 1732861967),
    ("Climbing Rope", 2999, "Durable outdoor rope", "Sports and Fitness", "Black Diamond", 4.8, 412, 609, 1732862967),
    ("Hiking Backpack", 4499, "50L trekking backpack", "Sports and Fitness", "Osprey", 4.9, 319, 508, 1732863967);

-- Games
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Chess Set", 999, "Wooden chess board with pieces", "Games", "Handcrafted Creations", 4.7, 523, 812, 1732864967),
    ("Playing Cards", 199, "Standard deck of 52 cards", "Games", "Bicycle", 4.8, 721, 1043, 1732865967),
    ("Board Game - Monopoly", 1499, "Classic property trading game", "Games", "Hasbro", 4.7, 634, 893, 1732866967),
    ("Jigsaw Puzzle", 499, "1000-piece nature scenery puzzle", "Games", "Ravensburger", 4.6, 541, 728, 1732867967),
    ("Video Game - Elden Ring", 3999, "Action role-playing game", "Games", "Bandai Namco", 4.9, 1032, 1547, 1732868967),
    ("Rubik's Cube", 499, "3x3 classic cube puzzle", "Games", "Rubik's", 4.8, 612, 921, 1732869967),
    ("Puzzle Cube Set", 899, "Set of 5 unique cubes", "Games", "Gan", 4.7, 538, 785, 1732870967),
    ("UNO Cards", 399, "Fun card game for all ages", "Games", "Mattel", 4.8, 763, 1094, 1732871967),
    ("Scrabble", 1499, "Word-building board game", "Games", "Hasbro", 4.7, 647, 935, 1732872967),
    ("Clue", 1299, "Mystery solving board game", "Games", "Hasbro", 4.6, 523, 749, 1732873967),
    ("Snakes and Ladders", 499, "Classic board game", "Games", "Funskool", 4.7, 442, 617, 1732874967),
    ("Dart Board", 1999, "Professional dartboard set", "Games", "Winmau", 4.8, 319, 497, 1732875967),
    ("Toy Train Set", 2999, "Electric toy train set", "Games", "Fisher-Price", 4.7, 453, 689, 1732876967),
    ("Racing Game", 3999, "Car racing video game", "Games", "Electronic Arts", 4.7, 528, 764, 1732877967),
    ("Role-Playing Dice Set", 999, "7-dice set for tabletop RPGs", "Games", "Chessex", 4.8, 438, 628, 1732878967),
    ("Beyblade", 799, "Spinning battle top", "Games", "Takara Tomy", 4.6, 517, 749, 1732879967),
    ("Model Building Kit", 1999, "Build and paint model set", "Games", "Tamiya", 4.7, 382, 531, 1732880967),
    ("Magic: The Gathering Cards", 2999, "Fantasy card deck", "Games", "Wizards of the Coast", 4.9, 654, 872, 1732881967),
    ("Catan", 2499, "Strategy board game", "Games", "Catan Studio", 4.8, 743, 1017, 1732882967),
    ("Laser Tag Guns", 4999, "Indoor laser tag set", "Games", "Nerf", 4.7, 439, 627, 1732883967);

-- Edibles
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Dark Chocolate", 299, "Rich and creamy chocolate", "Edibles", "Lindt", 4.8, 531, 846, 1732884967),
    ("Organic Honey", 499, "Pure and natural honey", "Edibles", "Dabur", 4.7, 426, 619, 1732885967),
    ("Green Tea", 199, "20 sachets of premium green tea", "Edibles", "Lipton", 4.6, 735, 1023, 1732886967),
    ("Trail Mix", 299, "Healthy nuts and dried fruits", "Edibles", "Happilo", 4.8, 542, 817, 1732887967),
    ("Instant Coffee", 349, "Premium freeze-dried coffee", "Edibles", "Nescafé", 4.7, 623, 914, 1732888967),
    ("Peanut Butter", 399, "Creamy peanut butter with no added sugar", "Edibles", "Pintola", 4.7, 452, 621, 1732889967),
    ("Almond Milk", 299, "Dairy-free almond milk", "Edibles", "Silk", 4.6, 511, 732, 1732890967),
    ("Multigrain Biscuits", 149, "Fiber-rich multigrain biscuits", "Edibles", "Britannia", 4.8, 614, 927, 1732891967),
    ("Energy Bars", 299, "Pack of 6 protein-packed energy bars", "Edibles", "Kind", 4.7, 548, 736, 1732892967),
    ("Oats", 249, "Whole grain rolled oats for a healthy breakfast", "Edibles", "Quaker", 4.7, 469, 602, 1732893967),
    ("Herbal Tea", 349, "Calming herbal tea with chamomile", "Edibles", "Twinings", 4.8, 519, 843, 1732894967),
    ("Pasta Sauce", 499, "Italian-style tomato and basil sauce", "Edibles", "Barilla", 4.6, 639, 915, 1732895967),
    ("Instant Noodles", 49, "Classic masala-flavored noodles", "Edibles", "Maggi", 4.7, 714, 1007, 1732896967),
    ("Coconut Water", 199, "100% natural tender coconut water", "Edibles", "Cocojal", 4.8, 453, 623, 1732897967),
    ("Gourmet Popcorn", 399, "Caramel and cheese flavored popcorn", "Edibles", "Act II", 4.7, 328, 489, 1732898967);

-- Home and Kitchen
INSERT INTO Products (name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought, createdAt)
VALUES
    ("Vacuum Cleaner", 6999, "Bagless upright vacuum cleaner", "Home and Kitchen", "Dyson", 4.7, 634, 812, 1732900967),
    ("Microwave Oven", 8499, "30L convection microwave", "Home and Kitchen", "LG", 4.8, 723, 937, 1732901967),
    ("Non-Stick Cookware Set", 2999, "5-piece cookware set", "Home and Kitchen", "Prestige", 4.6, 518, 732, 1732902967),
    ("Air Purifier", 12999, "HEPA filter air purifier", "Home and Kitchen", "Philips", 4.7, 612, 827, 1732903967),
    ("Electric Kettle", 1299, "1.5L stainless steel kettle", "Home and Kitchen", "Borosil", 4.6, 421, 589, 1732904967),
    ("Dishwasher", 24999, "Fully automatic dishwasher", "Home and Kitchen", "Bosch", 4.8, 749, 1053, 1732905967),
    ("Blender", 2599, "High-speed blender for smoothies", "Home and Kitchen", "Philips", 4.7, 526, 708, 1732906967),
    ("Refrigerator", 17999, "Double door refrigerator with inverter technology", "Home and Kitchen", "Samsung", 4.8, 845, 1227, 1732907967),
    ("Coffee Maker", 3999, "Espresso machine with milk frother", "Home and Kitchen", "Breville", 4.7, 624, 808, 1732908967),
    ("Induction Cooktop", 3999, "Portable induction cooktop with 3 heat settings", "Home and Kitchen", "Preethi", 4.6, 512, 738, 1732909967),
    ("Toaster", 1499, "2-slice toaster with browning control", "Home and Kitchen", "Crompton", 4.7, 438, 621, 1732910967),
    ("Electric Pressure Cooker", 6999, "Multi-function electric pressure cooker", "Home and Kitchen", "Prestige", 4.7, 634, 911, 1732911967),
    ("Water Purifier", 4999, "RO + UV water purifier", "Home and Kitchen", "Kent", 4.8, 729, 1006, 1732912967),
    ("Iron", 1999, "Steam iron with auto shut-off", "Home and Kitchen", "Philips", 4.7, 517, 716, 1732913967),
    ("Cordless Vacuum Cleaner", 8499, "Lightweight cordless vacuum with long battery life", "Home and Kitchen", "Dyson", 4.8, 643, 819, 1732914967);


-- Users
INSERT INTO Users (name, email, role, password, phoneNumber, address, pincode, state, money, createdAt)
VALUES
    ("John Doe", "john.doe@example.com", "Customer", "abcxyz", "9876543210", "123 Main Street, City", 110001, "California", 8500, 1732900967),
    ("Jane Smith", "jane.smith@example.com", "Customer", "defghi", "9123456789", "456 Oak Avenue, Town", 110002, "Texas", 7200, 1732901967),
    ("Robert Johnson", "robert.johnson@example.com", "Customer", "jklmno", "9876123456", "789 Pine Road, Village", 110003, "New York", 9500, 1732902967),
    ("Emily Davis", "emily.davis@example.com", "Customer", "pqrstu", "8765432109", "321 Birch Lane, Suburb", 110004, "Florida", 10500, 1732903967),
    ("Michael Brown", "michael.brown@example.com", "Customer", "vwxyzp", "8765123456", "654 Maple Drive, City", 110005, "Illinois", 6500, 1732904967),
    ("Sarah Wilson", "sarah.wilson@example.com", "Customer", "abcdeh", "9345678901", "123 Cedar Street, Town", 110006, "California", 7800, 1732905967),
    ("David Martinez", "david.martinez@example.com", "Customer", "hijklz", "9012345678", "987 Elm Boulevard, Village", 110007, "Texas", 9200, 1732906967),
    ("Sophia Garcia", "sophia.garcia@example.com", "Customer", "mnbvxy", "9787654321", "543 Willow Way, Suburb", 110008, "Florida", 11000, 1732907967),
    ("James Lee", "james.lee@example.com", "Customer", "stuvwx", "9456789012", "321 Maple Court, City", 110009, "New York", 6000, 1732908967),
    ("Olivia Gonzalez", "olivia.gonzalez@example.com", "Customer", "yzabcd", "9234567890", "789 Oak Lane, Town", 110010, "California", 11000, 1732909967),
    ("William Harris", "william.harris@example.com", "Customer", "efghij", "9678543201", "654 Birch Road, Village", 110011, "Texas", 7400, 1732910967),
    ("Isabella Clark", "isabella.clark@example.com", "Customer", "klmnop", "9654321098", "123 Pine Street, Suburb", 110012, "Florida", 8500, 1732911967),
    ("Benjamin Lewis", "benjamin.lewis@example.com", "Customer", "qrstuv", "9567890123", "321 Maple Lane, City", 110013, "Illinois", 9300, 1732912967),
    ("Charlotte Walker", "charlotte.walker@example.com", "Customer", "wxyzab", "9345123456", "654 Oak Boulevard, Town", 110014, "Texas", 8700, 1732913967),
    ("Lucas Hall", "lucas.hall@example.com", "Customer", "opqrst", "9234789098", "987 Elm Street, Village", 110015, "Florida", 6700, 1732914967),
    ("Mia Allen", "mia.allen@example.com", "Customer", "abcwxy", "9165678901", "123 Birch Court, Suburb", 110016, "New York", 10100, 1732915967),
    ("Elijah Young", "elijah.young@example.com", "Customer", "ghijkl", "9087654321", "321 Cedar Boulevard, City", 110017, "California", 6000, 1732916967),
    ("Amelia Hernandez", "amelia.hernandez@example.com", "Customer", "mnopqr", "8998765432", "789 Pine Road, Town", 110018, "Texas", 7500, 1732917967),
    ("Jack Scott", "jack.scott@example.com", "Customer", "abcdef", "9236456789", "987 Oak Street, Village", 110019, "Florida", 8000, 1732918967),
    ("Avery King", "avery.king@example.com", "Customer", "stuvwx", "9876543210", "543 Maple Lane, Suburb", 110020, "New York", 9500, 1732919967),
    ("Ethan Wright", "ethan.wright@example.com", "Customer", "yzabcv", "9123456789", "321 Oak Road, City", 110021, "California", 10600, 1732920967),
    ("Lily Martinez", "lily.martinez@example.com", "Customer", "ijklmn", "9456789012", "654 Pine Boulevard, Town", 110022, "Texas", 8700, 1732921967),
    ("Mason Lee", "mason.lee@example.com", "Customer", "opqrst", "9678342109", "789 Oak Court, Village", 110023, "Florida", 6700, 1732922967),
    ("Zoe Perez", "zoe.perez@example.com", "Customer", "uvwxyz", "9087432165", "123 Cedar Boulevard, Suburb", 110024, "New York", 7200, 1732923967),
    ("Matthew Taylor", "matthew.taylor@example.com", "Customer", "mnopqr", "9236789098", "654 Maple Court, City", 110025, "California", 8300, 1732924967),
    ("Ella Anderson", "ella.anderson@example.com", "Customer", "abcdef", "9345678901", "987 Oak Lane, Town", 110026, "Texas", 8900, 1732925967),
    ("David Thomas", "david.thomas@example.com", "Customer", "ghijkl", "9456789012", "123 Birch Court, Village", 110027, "Florida", 9500, 1732926967),
    ("Chloe Moore", "chloe.moore@example.com", "Customer", "wxyzab", "9678342109", "789 Maple Boulevard, Suburb", 110028, "New York", 6700, 1732927967),
    ("Daniel Martinez", "daniel.martinez@example.com", "Customer", "rstuvw", "9087654321", "543 Oak Road, City", 110029, "California", 7200, 1732928967),
    ("Sophia Wilson", "sophia.wilson@example.com", "Customer", "abcdef", "9456789012", "789 Birch Court, Village", 110030, "Florida", 8900, 1732929967),
    ("James Garcia", "james.garcia@example.com", "Customer", "ghijkl", "9123456789", "123 Maple Boulevard, Suburb", 110031, "New York", 7400, 1732930967),
    ("Olivia Brown", "olivia.brown@example.com", "Customer", "mnopqr", "9236789098", "654 Oak Lane, Town", 110032, "Texas", 6700, 1732931967),
    ("Benjamin Harris", "benjamin.harris@example.com", "Customer", "abcdef", "9345678901", "987 Pine Street, Village", 110033, "California", 8000, 1732932967),
    ("Ella Walker", "ella.walker@example.com", "Customer", "ghijkl", "9456789012", "321 Birch Road, City", 110034, "Florida", 10600, 1732933967),
    ("Daniel Scott", "daniel.scott@example.com", "Customer", "rstuvw", "9165678901", "654 Maple Boulevard, Town", 110035, "New York", 9200, 1732934967),
    ("Chloe Johnson", "chloe.johnson@example.com", "Customer", "xyzabc", "9876543210", "123 Oak Lane, Village", 110036, "Texas", 10600, 1732935967),
    ("Lily Martin", "lily.martin@example.com", "Customer", "ijklmn", "9087654321", "987 Birch Court, Suburb", 110037, "California", 8500, 1732936967),
    ("Lucas Taylor", "lucas.taylor@example.com", "Customer", "opqrst", "9678342109", "543 Cedar Boulevard, City", 110038, "Florida", 7200, 1732937967),
    ("Madison Evans", "madison.evans@example.com", "Customer", "abcdef", "9456789012", "789 Willow Way, Village", 110039, "New York", 8700, 1732938967),
    ("Mason Allen", "mason.allen@example.com", "Customer", "mnopqr", "9087654321", "321 Pine Boulevard, Suburb", 110040, "Texas", 9500, 1732939967),
    ("Ava King", "ava.king@example.com", "Customer", "wxyzab", "9234567890", "987 Birch Road, City", 110041, "California", 7800, 1732940967),
    ("Elijah Lopez", "elijah.lopez@example.com", "Customer", "opqrst", "9456789012", "543 Oak Court, Suburb", 110042, "Florida", 9000, 1732941967),
    ("James Young", "james.young@example.com", "Customer", "abcdef", "9165678901", "321 Maple Court, Town", 110043, "New York", 7200, 1732942967),
    ("Mia Wilson", "mia.wilson@example.com", "Customer", "ghijkl", "9678342109", "789 Cedar Boulevard, City", 110044, "Texas", 10600, 1732943967),
    ("Aiden Perez", "aiden.perez@example.com", "Customer", "mnopqr", "9345678901", "123 Birch Road, Village", 110045, "California", 6800, 1732944967),
    ("Chloe Harris", "chloe.harris@example.com", "Customer", "qrstuv", "9087654321", "654 Oak Boulevard, Suburb", 110046, "New York", 10600, 1732945967),
    ("Sophia Gonzalez", "sophia.gonzalez@example.com", "Customer", "abcdef", "9456789012", "987 Pine Road, Town", 110047, "Florida", 8900, 1732946967),
    ("Liam Scott", "liam.scott@example.com", "Customer", "opqrst", "9345678901", "123 Cedar Court, City", 110048, "Texas", 8000, 1732947967),
    ("Jack Moore", "jack.moore@example.com", "Customer", "ghijkl", "9678342109", "543 Oak Lane, Suburb", 110049, "New York", 7800, 1732948967),
    ("Amelia Taylor", "amelia.taylor@example.com", "Customer", "rstuvw", "9678342109", "321 Birch Boulevard, Town", 110050, "California", 8500, 1732949967);

-- Orders