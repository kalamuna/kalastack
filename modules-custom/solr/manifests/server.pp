/**
 * 
 * Defines and sets default values for the server.xml
 * 
 */
define solr::server (
    
  # basic settings
  $path = "/etc/tomcat6/server.xml",
  $port = 8983,
  
) {
  
  file {
    "${path}":
      path      => "${path}",
      content   => template("solr/server.xml.erb"),
  }
  
}