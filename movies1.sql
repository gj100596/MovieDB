-- MySQL dump 10.13  Distrib 5.6.20, for Win64 (x86_64)
--
-- Host: localhost    Database: moviedb
-- ------------------------------------------------------
-- Server version	5.6.20

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `movie`
--

DROP TABLE IF EXISTS `movie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `movie` (
  `vote_count` int(11) DEFAULT NULL,
  `id` int(11) NOT NULL DEFAULT '1',
  `vote_average` decimal(2,1) DEFAULT NULL,
  `title` varchar(54) DEFAULT NULL,
  `popularity` decimal(9,6) DEFAULT NULL,
  `poster_path` varchar(32) DEFAULT NULL,
  `genre_ids` int(11) DEFAULT NULL,
  `overview` varchar(581) DEFAULT NULL,
  `release_date` date DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `movie`
--

LOCK TABLES `movie` WRITE;
/*!40000 ALTER TABLE `movie` DISABLE KEYS */;
INSERT INTO `movie` VALUES (6501,1,7.4,'Pirates of the Caribbean: The Curse of the Black Pearl',25.880528,'/tkt9xR1kNX5R9rCebASKck44si2.jpg',28,'Jack Sparrow, a freewheeling 17th-century pirate who roams the Caribbean Sea, butts heads with a rival pirate bent on pillaging the village of Port Royal. When the governor\'s daughter is kidnapped, Sparrow decides to help the girl\'s love save her. But their seafaring mission is hardly simple.','2003-07-09'),(4008,2,7.0,'Rise of the Planet of the Apes',28.364664,'/esqXMJv6PiK7GJVRwd2FA3SZUoW.jpg',878,'Scientist Will Rodman is determined to find a cure for Alzheimer\'s, the disease which has slowly consumed his father. Will feels certain he is close to a breakthrough and tests his latest serum on apes, noticing dramatic increases in intelligence and brain activity in the primate subjects   especially Caesar, his pet chimpanzee.','2011-08-03'),(8884,3,7.2,'Mad Max: Fury Road',28.419367,'/kqjL17yufvn9OVLyXYpvtyrFfak.jpg',53,'An apocalyptic story set in the furthest reaches of our planet, in a stark desert landscape where humanity is broken, and most everyone is crazed fighting for the necessities of life. Within this world exist two rebels on the run who just might be able to restore order. There\'s Max, a man of action and a man of few words, who seeks peace of mind following the loss of his wife and child in the aftermath of the chaos. And Furiosa, a woman of action and a woman who believes her path to survival may be achieved if she can make it across the desert back to her childhood homeland.','2015-05-13'),(8968,4,7.9,'Guardians of the Galaxy',39.930463,'/y31QB9kn3XSudA15tV7UWQ9XLuW.jpg',12,'Light years from Earth, 26 years after being abducted, Peter Quill finds himself the prime target of a manhunt after discovering an orb wanted by Ronan the Accuser.','2014-07-30'),(4089,5,7.3,'Dawn of the Planet of the Apes',34.938561,'/2EUAUIu5lHFlkj5FRryohlH6CRO.jpg',53,'A group of scientists in San Francisco struggle to stay alive in the aftermath of a plague that is wiping out humanity, while Caesar tries to maintain dominance over his community of intelligent apes.','2014-06-26'),(1946,6,5.7,'Alien: Covenant',31.697763,'/zecMELPbU5YMQpC81Z8ImaaXuf9.jpg',53,'Bound for a remote planet on the far side of the galaxy, the crew of the colony ship \'Covenant\' discovers what is thought to be an uncharted paradise, but is actually a dark, dangerous world   which has its sole inhabitant the \'synthetic\', David, survivor of the doomed Prometheus expedition.','2017-05-09'),(8160,7,6.5,'Jurassic World',27.027944,'/jjBgi2r5cRt36xF6iNUEhzscEcb.jpg',53,'Twenty-two years after the events of Jurassic Park, Isla Nublar now features a fully functioning dinosaur theme park, Jurassic World, as originally envisioned by John Hammond.','2015-06-09'),(10061,8,8.1,'Interstellar',30.869445,'/nBNZadXqJSdt05SHLqgT0HuC5Gm.jpg',878,'Interstellar chronicles the adventures of a group of explorers who make use of a newly discovered wormhole to surpass the limitations on human space travel and conquer the vast distances involved in an interstellar voyage.','2014-11-05'),(4020,9,6.4,'Minions',208.801149,'/q0R4crx2SehcEEQEkYObktdeFy.jpg',35,'Minions Stuart, Kevin and Bob are recruited by Scarlet Overkill, a super-villain who, alongside her inventor husband Herb, hatches a plot to take over the world.','2015-06-17'),(955,10,6.5,'King Arthur: Legend of the Sword',25.277856,'/qyXPqzlCWf3T9VEpBtquUQZwsgi.jpg',14,'When the child Arthur s father is murdered, Vortigern, Arthur s uncle, seizes the crown. Robbed of his birthright and with no idea who he truly is, Arthur comes up the hard way in the back alleys of the city. But once he pulls the sword Excalibur from the stone, his life is turned upside down and he is forced to acknowledge his true legacy... whether he likes it or not.','2017-04-27'),(935,11,6.7,'War for the Planet of the Apes',45.020644,'/y52mjaCLoJJzxfcDDlksKDngiDx.jpg',10752,'Caesar and his apes are forced into a deadly conflict with an army of humans led by a ruthless Colonel. After the apes suffer unimaginable losses, Caesar wrestles with his darker instincts and begins his own mythic quest to avenge his kind. As the journey finally brings them face to face, Caesar and the Colonel are pitted against each other in an epic battle that will determine the fate of both their species and the future of the planet.','2017-07-11'),(2783,12,6.5,'Miss Peregrine\'s Home for Peculiar Children',26.364150,'/AvekzUdI8HZnImdQulmTTmAZXrC.jpg',12,'A teenager finds himself transported to an island where he must help protect a group of orphans with special powers from creatures intent on destroying them.','2016-09-28'),(10028,13,7.4,'Deadpool',32.123235,'/inVq3FRqcYIRl2la8iZikYYxFNR.jpg',10749,'Based upon Marvel Comics  most unconventional anti-hero, DEADPOOL tells the origin story of former Special Forces operative turned mercenary Wade Wilson, who after being subjected to a rogue experiment that leaves him with accelerated healing powers, adopts the alter ego Deadpool. Armed with his new abilities and a dark, twisted sense of humor, Deadpool hunts down the man who nearly destroyed his life.','2016-02-09'),(2239,14,7.4,'Spider-Man: Homecoming',96.251757,'/c24sv2weTHPsmDa7jEMN0m2P3RT.jpg',878,'Following the events of Captain America: Civil War, Peter Parker, with the help of his mentor Tony Stark, tries to balance his life as an ordinary high school student in Queens, New York City, with fighting crime as his superhero alter ego Spider-Man as a new threat, the Vulture, emerges.','2017-07-05'),(1962,15,5.9,'Ghost in the Shell',27.404901,'/myRzRzCxdfUWjkJWgpHHZ1oGkJd.jpg',53,'In the near future, Major is the first of her kind: a human saved from a terrible crash, then cyber-enhanced to be a perfect soldier devoted to stopping the world\'s most dangerous criminals.','2017-03-29'),(4526,16,6.8,'Beauty and the Beast',102.070200,'/tWqifoYuwLETmmasnGHO7xBjEtt.jpg',10749,'A live-action adaptation of Disney\'s version of the classic \'Beauty and the Beast\' tale of a cursed prince and a beautiful young woman who helps him break the spell.','2017-03-16'),(1173,17,6.2,'Despicable Me 3',57.019245,'/5qcUGqWoWhEsoQwNUrtf3y3fcWn.jpg',10751,'Gru and his wife Lucy must stop former \'80s child star Balthazar Bratt from achieving world domination.','2017-06-15'),(106,18,5.6,'The Dark Tower',22.983700,'/i9GUSgddIqrroubiLsvvMRYyRy0.jpg',27,'The last Gunslinger, Roland Deschain, has been locked in an eternal battle with Walter O Dim, also known as the Man in Black, determined to prevent him from toppling the Dark Tower, which holds the universe together. With the fate of the worlds at stake, good and evil will collide in the ultimate battle as only Roland can defend the Tower from the Man in Black.','2017-08-03'),(1199,19,7.4,'Dunkirk',45.445793,'/cUqEgoP6kj8ykfNjJx3Tl5zHCcN.jpg',10752,'Miraculous evacuation of Allied soldiers from Belgium, Britain, Canada, and France, who were cut off and surrounded by the German army from the beaches and harbor of Dunkirk, France, between May 26 and June 04, 1940, during Battle of France in World War II.','2017-07-19'),(105,20,6.9,'Annabelle: Creation',25.737237,'/tb86j8jVCVsdZnzf8I6cIi65IeM.jpg',27,'Several years after the tragic death of their little girl, a dollmaker and his wife welcome a nun and several girls from a shuttered orphanage into their home, soon becoming the target of the dollmaker\'s possessed creation, Annabelle.','2017-08-09');
/*!40000 ALTER TABLE `movie` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-08-14 23:03:52
