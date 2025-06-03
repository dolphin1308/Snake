# User Management System

A Java web application for managing user information with CRUD operations and Excel import functionality.

## Features

- View all users
- Search for a specific user
- Add a new user
- Update existing user
- Delete a user
- Import users from Excel files

## Technical Stack

- Java 8
- JSP
- Servlet
- MySQL
- Maven
- Apache POI (for Excel handling)

## Setup Instructions

### Database Setup

1. Install MySQL if you haven't already
2. Run the SQL script in `src/main/resources/user.sql` to create the database and tables
   ```
   mysql -u root -p < src/main/resources/user.sql
   ```

### Project Setup

1. Clone this repository
2. Open the project in your favorite Java IDE
3. Make sure Maven is installed
4. Update the database connection settings in `com.dolphin.dbutil.Dbconn` if necessary

### Build and Deploy

1. Build the project using Maven:
   ```
   mvn clean package
   ```
2. Deploy the generated WAR file to Tomcat:
   - Copy the `target/UserManagement.war` file to your Tomcat's `webapps` directory
   - Start Tomcat

## Usage

1. Access the application at `http://localhost:8080/UserManagement`
2. Use the main menu to navigate to different features

### Excel Import Format

For importing users from Excel, prepare your file with the following columns:
1. ID (number)
2. Name (text)
3. Password (text)

The first row should be a header row.

## License

This project is open source. 