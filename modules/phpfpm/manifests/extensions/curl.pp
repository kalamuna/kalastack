/**
 * 
 * Installs and configures the CURL extension for PHP5
 * 
 */
class phpfpm::extensions::curl {

  phpfpm::extension { "php5-curl": version => "5.3.10-1ubuntu3.4", }
  
}