/**
 * Hi dear user,
 * If you are here it's for configuration i suppose.
 * So if you want to configure you sharing path, juste copy and paste the folloing line
 * #define SHARING_PATH "yourpath"
 * Copy starting from # and ending at the second ".
 * 
 * Then replace "yourpath" by an ABSOLUTE path !
 * If you want to remove you setting, you could comment your line by adding "//" at start of it
 *
 * /!\ After changing that file you need ton recompile with the commande "make rebuild"
 *      Or By following the "Windows compatibility" file.
 *
 * /!\ You need to define ONLY ONE LINE in this file.
 *     
 * /!\ If you are on linux, you can't use the "~", all path need to be absolute.
 *
 * See exemple at end of file, you could use it by removing "//" 
 */ 
 
/* Exemple 1 - Linux */

// #define SHARING_PATH "/home/kaldoran/sharing"

/* Exemple 2 - Windows */

/**
 * This one will download / use your desktop as sharing path
 * Be carefull to replace "MyName" by your windows username 
 */
// #define SHARING_PATH "C://Users/MyName/Desktop"

/* Exemple 3 - Relative */

/**
 * Relative path could be use, but if you use a relative path, 
 * This will apply from where you start you programe
 * These 2 got the same path :
 */

// #define SHARING_PATH "sharing"
// #define SHARING_PATH "./sharing"
