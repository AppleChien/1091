-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2.1
-- http://www.phpmyadmin.net
--
-- 主機: localhost
-- 產生時間： 2020 年 12 月 16 日 15:59
-- 伺服器版本: 5.7.30-0ubuntu0.16.04.1
-- PHP 版本： 7.0.33-0ubuntu0.16.04.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `1091Web`
--

-- --------------------------------------------------------

--
-- 資料表結構 `HW4`
--

CREATE TABLE `HW4` (
  `folder` varchar(24) NOT NULL,
  `filename` varchar(24) NOT NULL,
  `name` varchar(24) DEFAULT NULL,
  `xmin` int(4) DEFAULT NULL,
  `ymin` int(4) DEFAULT NULL,
  `xmax` int(4) DEFAULT NULL,
  `ymax` int(4) DEFAULT NULL,
  `valid` tinyint(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- 資料表的匯出資料 `HW4`
--

INSERT INTO `HW4` (`folder`, `filename`, `name`, `xmin`, `ymin`, `xmax`, `ymax`, `valid`) VALUES
('pic', 'bird1.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'bird2.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'bird3.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'bird4.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'bird5.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'cat1.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'cat2.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'cat3.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'cat4.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'cat5.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'dog1.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'dog2.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'dog3.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'dog4.jpg', NULL, NULL, NULL, NULL, NULL, NULL),
('pic', 'dog5.jpg', NULL, NULL, NULL, NULL, NULL, NULL);

--
-- 已匯出資料表的索引
--

--
-- 資料表索引 `HW4`
--
ALTER TABLE `HW4`
  ADD PRIMARY KEY (`filename`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
