/**
 * 
 * Installs and configures the PEAR extension for PHP5
 * 
 */
class phpfpm::extensions::pear {

  phpfpm::extension { "php-pear": version => present, }
  
}