-- mod-polish-translation: accounts that asked for Polish texts (".polski on").
CREATE TABLE IF NOT EXISTS `mod_polish_translation_account` (
  `account` INT UNSIGNED NOT NULL,
  PRIMARY KEY (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
