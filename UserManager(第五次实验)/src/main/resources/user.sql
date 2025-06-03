DROP DATABASE IF EXISTS `mydatabase`;
CREATE DATABASE `mydatabase` DEFAULT CHARACTER SET utf8mb4;
USE `mydatabase`;

CREATE TABLE `user` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) default NULL,
  `password` varchar(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;

INSERT INTO `user` VALUES (1, 'admin', 'admin');
INSERT INTO `user` VALUES (2, 'user1', 'password1');
INSERT INTO `user` VALUES (3, 'user2', 'password2'); 