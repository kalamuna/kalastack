/**
 * 
 * Nothing special, just a basic version of git
 * 
 */
class webgrind::install {

  exec { "install-webgrind":
    path => "/bin:/usr/bin",
    unless => "cat /usr/share/webgrind/index.php",
    command => "wget http://webgrind.googlecode.com/files/webgrind-release-1.0.zip -O /tmp/grind.zip && unzip /tmp/grind.zip -d /usr/share/",
    require => [Class["phpfpm::extensions::xdebug"], Class["unzip::install"]],
  }  
  
}
