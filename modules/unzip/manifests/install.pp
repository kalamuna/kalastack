/**
 * 
 * Install unzip
 */
class unzip::install {
    
   package { "unzip":
    ensure => "6.0-4ubuntu1",
  }
    
}
