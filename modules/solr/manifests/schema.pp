/**
 * 
 * Defines and sets default values for the schema.pp
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