### How to manage Database for this project
> most important commands:
    - create database ["name"];
    - create table ["name"] (column1 datatype,column2 datatype,column3 datatype, ...);
    - show tables;

    ## Creating user
    - create user 'someName'@'<your-ip-here>' Identified by '<choose a password here>' ;
        "i would recommend to put instead of your devices-IP a '%' instead, so that the database accepts you with any IP.
    - GRANT ALL ON *.* TO 'someName'@'<your-ip-here>' IDENTIFIED BY '<choose a password here>';
        "grant rights for the user";
    - SHOW GRANTS FOR 'someName'@'<your-ip-here>';
    - flush privileges;

    ## managing table
    - delete from ["tablename];
        "deletes all records"
    - select * from ["tablename"];
        "selects all columns from table"