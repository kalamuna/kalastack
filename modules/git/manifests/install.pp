/**
 * 
 * Nothing special, just a basic version of git
 * 
 */
class git::install {
    
  package { "git-core":
    ensure => present,
  }
  
}
