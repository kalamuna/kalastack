/**
 * 
 * Installs and configures the IMAP extension for PHP5
 * 
 */
class phpfpm::extensions::imap {

  phpfpm::extension { "php5-imap": version => present, }
  
}