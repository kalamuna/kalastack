/**
 * 
 * Defines and sets default values for the solrconf
 * 
 */
define solr::solrconf (
    
  # basic settings
  $path = "/etc/solr/conf/solrconfig.xml",
  
) {
  
  file {
    "${path}":
      path      => "${path}",
      content   => template("solr/solrconfig.xml.erb"),
  }
  
}