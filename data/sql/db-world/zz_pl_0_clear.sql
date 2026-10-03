-- mod-polish-translation: free the borrowed koKR slot. The Polish texts are stored under koKR
-- (README, "Borrowed locale slot"); the Korean rows shipped with AzerothCore would show up wherever
-- there is no Polish text, so they are removed and the core falls back to English there.
-- Never edit this file: a changed file is applied again and would wipe the Polish rows of the
-- zone files, which are not applied again. Put later cleanups into a new file.

DELETE FROM `quest_template_locale` WHERE `locale` = 'koKR';
DELETE FROM `quest_offer_reward_locale` WHERE `locale` = 'koKR';
DELETE FROM `quest_request_items_locale` WHERE `locale` = 'koKR';
DELETE FROM `quest_greeting_locale` WHERE `locale` = 'koKR';
DELETE FROM `creature_template_locale` WHERE `locale` = 'koKR';
DELETE FROM `gameobject_template_locale` WHERE `locale` = 'koKR';
DELETE FROM `item_template_locale` WHERE `locale` = 'koKR';
DELETE FROM `page_text_locale` WHERE `locale` = 'koKR';
DELETE FROM `npc_text_locale` WHERE `Locale` = 'koKR';
DELETE FROM `gossip_menu_option_locale` WHERE `Locale` = 'koKR';
DELETE FROM `points_of_interest_locale` WHERE `locale` = 'koKR';
DELETE FROM `trainer_locale` WHERE `locale` = 'koKR';
DELETE FROM `creature_text_locale` WHERE `Locale` = 'koKR';
DELETE FROM `broadcast_text_locale` WHERE `locale` = 'koKR';
DELETE FROM `achievement_reward_locale` WHERE `Locale` = 'koKR';
DELETE FROM `item_set_names_locale` WHERE `locale` = 'koKR';
DELETE FROM `pet_name_generation_locale` WHERE `locale` = 'koKR';
UPDATE `acore_string` SET `locale_koKR` = NULL WHERE `locale_koKR` IS NOT NULL;
