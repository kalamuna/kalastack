/**
 * 
 * Defines and sets default values for a my.cnf file
 * 
 */
define solr::schema (
    
  # basic settings
  $path = "/etc/solr/conf/schema.xml",
  
) {
  
  file {
    "${path}":
      path      => "${path}",
      content   => template("solr/schema.xml.erb"),
  }
  
}