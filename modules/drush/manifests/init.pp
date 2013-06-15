/**
 * 
 * Installs drush and provides some custom commands
 * 
 */
class drush {
    
  include drush::install, drush::upgrade, drush::config, drush::sqlsync
  
}