/**
 * 
 * Installs and configures the PEAR extension for PHP5
 * 
 */
class phpfpm::extensions::pear {

  phpfpm::extension { "php-pear": version => "5.3.10-1ubuntu3.4", }
  
}