<?php

/**
 * Implementation of hook_views_default_views().
 */
function atomicreach_views_default_views() {
    $view = new view;
    $view->name = 'AR_Feed';
    $view->description = 'Generates RSS feed of latest 300 article with ull content.';
    $view->tag = '';
    $view->base_table = 'node';
    $view->core = 6;
    $view->api_version = '2';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    $handler = $view->new_display('default', 'Defaults', 'default');
    $handler->override_option('fields', array(
        'body' => array(
            'label' => 'Body',
            'alter' => array(
                'alter_text' => 0,
                'text' => '',
                'make_link' => 0,
                'path' => '',
                'absolute' => 0,
                'link_class' => '',
                'alt' => '',
                'rel' => '',
                'prefix' => '',
                'suffix' => '',
                'target' => '',
                'help' => '',
                'trim' => 0,
                'max_length' => '',
                'word_boundary' => 1,
                'ellipsis' => 1,
                'html' => 0,
                'strip_tags' => 0,
            ),
            'empty' => '',
            'hide_empty' => 0,
            'empty_zero' => 0,
            'hide_alter_empty' => 1,
            'exclude' => 0,
            'id' => 'body',
            'table' => 'node_revisions',
            'field' => 'body',
            'relationship' => 'none',
        ),
        'view_node' => array(
            'label' => 'Link',
            'alter' => array(
                'alter_text' => 0,
                'text' => '',
                'make_link' => 0,
                'path' => '',
                'absolute' => 0,
                'link_class' => '',
                'alt' => '',
                'rel' => '',
                'prefix' => '',
                'suffix' => '',
                'target' => '',
                'help' => '',
                'trim' => 0,
                'max_length' => '',
                'word_boundary' => 1,
                'ellipsis' => 1,
                'html' => 0,
                'strip_tags' => 0,
            ),
            'empty' => '',
            'hide_empty' => 0,
            'empty_zero' => 0,
            'hide_alter_empty' => 1,
            'text' => '',
            'exclude' => 0,
            'id' => 'view_node',
            'table' => 'node',
            'field' => 'view_node',
            'relationship' => 'none',
        ),
        'nid' => array(
            'label' => 'Nid',
            'alter' => array(
                'alter_text' => 0,
                'text' => '',
                'make_link' => 0,
                'path' => '',
                'absolute' => 0,
                'link_class' => '',
                'alt' => '',
                'rel' => '',
                'prefix' => '',
                'suffix' => '',
                'target' => '',
                'help' => '',
                'trim' => 0,
                'max_length' => '',
                'word_boundary' => 1,
                'ellipsis' => 1,
                'html' => 0,
                'strip_tags' => 0,
            ),
            'empty' => '',
            'hide_empty' => 0,
            'empty_zero' => 0,
            'hide_alter_empty' => 1,
            'link_to_node' => 0,
            'exclude' => 0,
            'id' => 'nid',
            'table' => 'node',
            'field' => 'nid',
            'relationship' => 'none',
        ),
        'created' => array(
            'label' => 'Post date',
            'alter' => array(
                'alter_text' => 0,
                'text' => '',
                'make_link' => 0,
                'path' => '',
                'absolute' => 0,
                'link_class' => '',
                'alt' => '',
                'rel' => '',
                'prefix' => '',
                'suffix' => '',
                'target' => '',
                'help' => '',
                'trim' => 0,
                'max_length' => '',
                'word_boundary' => 1,
                'ellipsis' => 1,
                'html' => 0,
                'strip_tags' => 0,
            ),
            'empty' => '',
            'hide_empty' => 0,
            'empty_zero' => 0,
            'hide_alter_empty' => 1,
            'date_format' => 'small',
            'custom_date_format' => '',
            'exclude' => 0,
            'id' => 'created',
            'table' => 'node',
            'field' => 'created',
            'relationship' => 'none',
        ),
        'title' => array(
            'label' => 'Title',
            'alter' => array(
                'alter_text' => 0,
                'text' => '',
                'make_link' => 0,
                'path' => '',
                'absolute' => 0,
                'link_class' => '',
                'alt' => '',
                'rel' => '',
                'prefix' => '',
                'suffix' => '',
                'target' => '',
                'help' => '',
                'trim' => 0,
                'max_length' => '',
                'word_boundary' => 1,
                'ellipsis' => 1,
                'html' => 0,
                'strip_tags' => 0,
            ),
            'empty' => '',
            'hide_empty' => 0,
            'empty_zero' => 0,
            'hide_alter_empty' => 1,
            'link_to_node' => 1,
            'exclude' => 0,
            'id' => 'title',
            'table' => 'node',
            'field' => 'title',
            'relationship' => 'none',
        ),
    ));
    $handler->override_option('sorts', array(
        'created' => array(
            'order' => 'DESC',
            'granularity' => 'second',
            'id' => 'created',
            'table' => 'node',
            'field' => 'created',
            'relationship' => 'none',
        ),
        'status' => array(
            'order' => 'DESC',
            'id' => 'status',
            'table' => 'node',
            'field' => 'status',
            'relationship' => 'none',
        ),
    ));
    $handler->override_option('filters', array(
        'status' => array(
            'operator' => '=',
            'value' => '1',
            'group' => '0',
            'exposed' => FALSE,
            'expose' => array(
                'operator' => FALSE,
                'label' => '',
            ),
            'id' => 'status',
            'table' => 'node',
            'field' => 'status',
            'relationship' => 'none',
        ),
    ));
    $handler->override_option('access', array(
        'type' => 'none',
    ));
    $handler->override_option('cache', array(
        'type' => 'none',
    ));
    $handler->override_option('distinct', 1);
    $handler = $view->new_display('feed', 'Feed', 'feed_1');
    $handler->override_option('items_per_page', 300);
    $handler->override_option('style_plugin', 'rss');
    $handler->override_option('style_options', array(
        'mission_description' => FALSE,
        'description' => '',
    ));
    $handler->override_option('row_plugin', 'node_rss');
    $handler->override_option('row_options', array(
        'relationship' => 'none',
        'item_length' => 'fulltext',
    ));
    $handler->override_option('path', 'feed/arfeed.xml');
    $handler->override_option('menu', array(
        'type' => 'none',
        'title' => '',
        'description' => '',
        'weight' => 0,
        'name' => 'navigation',
    ));
    $handler->override_option('tab_options', array(
        'type' => 'none',
        'title' => '',
        'description' => '',
        'weight' => 0,
        'name' => 'navigation',
    ));
    $handler->override_option('displays', array(
        'default' => 'default',
    ));
    $handler->override_option('sitename_title', 1);

    $views[$view->name] = $view;
    return $views;
}
