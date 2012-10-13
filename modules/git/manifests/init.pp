/**
 * 
 * Nothing special, just a basic version of git
 * 
 */
class git {
    
  package { "git-core":
    ensure => "1:1.7.9.5-1",
  }
  
}
