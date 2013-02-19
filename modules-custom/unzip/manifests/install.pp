/**
 * 
 * Install unzip
 */
class unzip::install {
    
   package { "unzip":
    ensure => "present",
  }
    
}
