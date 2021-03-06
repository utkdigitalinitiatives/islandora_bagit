<?php

/**
 * @file
 * Plugin for the Islandora BagIt Drupal module.
 *
 * Adds a PREMIS metadata file as generated by the Islandora PREMIS
 * module.
 */

/**
 * Returns an array of source and destination file paths.
 *
 * @param object $islandora_object
 *   The Islandora object to create a Bag for.
 *
 * @param string $tmp_ds_directory
 *   The temporary directory where the datastream files have been downloaded.
 *
 * @return array|bool
 *   An array of source and destination file paths, or FALSE
 *   if no datastream files are present.
 */
function islandora_bagit_plugin_object_premis_init($islandora_object, $tmp_ds_directory) {
  $files_to_add = array();
  if (module_exists('islandora_premis')) {
    module_load_include('inc', 'islandora_premis', 'includes/utilities');
    $premis_xml = islandora_premis_transform_foxml_to_premis($islandora_object);
  }
  else {
    return FALSE;
  }

  $premis_file_path = $tmp_ds_directory . DIRECTORY_SEPARATOR . 'premis.xml';
  file_put_contents($premis_file_path, $premis_xml);
  $files_to_add[] = array(
    'source' => $premis_file_path,
    'dest' => 'PREMIS.xml',
  );

  if (count($files_to_add)) {
    return $files_to_add;
  }
  else {
    return FALSE;
  }
}
