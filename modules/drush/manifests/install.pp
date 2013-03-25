/**
 * 
 * Installs drush
 * 
 */
class drush::install {
	
  package { "drush":
    ensure   => present,
  }
  
}