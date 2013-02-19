/**
 * 
 * Installs and configures the IMAP extension for PHP5
 * 
 */
class phpfpm::extensions::imap {

  phpfpm::extension { "php5-imap": version => "5.3.5-0ubuntu2", }
  
}