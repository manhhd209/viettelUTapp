-- MySQL dump 10.16  Distrib 10.1.38-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: viettelapp
-- ------------------------------------------------------
-- Server version	10.1.38-MariaDB-0ubuntu0.18.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `permission`
--

DROP TABLE IF EXISTS `permission`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `permission` (
  `pmsid` int(11) NOT NULL AUTO_INCREMENT,
  `pmsname` varchar(40) NOT NULL,
  PRIMARY KEY (`pmsid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `permission`
--

LOCK TABLES `permission` WRITE;
/*!40000 ALTER TABLE `permission` DISABLE KEYS */;
INSERT INTO `permission` VALUES (1,'Change Permission'),(2,'View Dashboard'),(3,'View Config'),(4,'Permission X');
/*!40000 ALTER TABLE `permission` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usePpermission`
--

DROP TABLE IF EXISTS `usePpermission`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `usePpermission` (
  `upId` int(11) NOT NULL AUTO_INCREMENT,
  `userId` int(11) NOT NULL,
  `pmsId` int(11) NOT NULL,
  PRIMARY KEY (`upId`),
  KEY `userId` (`userId`),
  KEY `pmsId` (`pmsId`),
  CONSTRAINT `usePpermission_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `vtuser` (`userid`) ON DELETE CASCADE,
  CONSTRAINT `usePpermission_ibfk_2` FOREIGN KEY (`pmsId`) REFERENCES `permission` (`pmsid`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `usePpermission`
--

LOCK TABLES `usePpermission` WRITE;
/*!40000 ALTER TABLE `usePpermission` DISABLE KEYS */;
INSERT INTO `usePpermission` VALUES (1,1,1),(2,1,2),(3,1,3);
/*!40000 ALTER TABLE `usePpermission` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vtuser`
--

DROP TABLE IF EXISTS `vtuser`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vtuser` (
  `userid` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(40) NOT NULL,
  `password` varchar(40) NOT NULL,
  `displayname` varchar(100) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`userid`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vtuser`
--

LOCK TABLES `vtuser` WRITE;
/*!40000 ALTER TABLE `vtuser` DISABLE KEYS */;
INSERT INTO `vtuser` VALUES (1,'test1','123','Tai khoan test'),(2,'test2','123','Tai khoan test 2'),(3,'test3','123','Tai khoan test 3'),(4,'test4','123','Tai khoan test 4'),(5,'test5','123','Tai khoan test 5');
/*!40000 ALTER TABLE `vtuser` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-02-25  3:58:43
