/**
 * 
 * install a basic version of vim
 * 
 */
class vim::install {
    
  package { "vim":
    ensure => present,
  }
  
}
