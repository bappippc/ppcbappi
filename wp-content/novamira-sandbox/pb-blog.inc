<?php
/**
 * PPC BAPPI blog layer: archive (blog, category, tag, search) and single post templates.
 */
if ( ! defined( 'ABSPATH' ) ) { exit; }

function pb_blog_is_list() {
	return is_home() || is_category() || is_tag() || is_search() || is_author() || is_date();
}

add_filter( 'template_include', function ( $t ) {
	if ( pb_blog_is_list() ) { return __DIR__ . '/pb-tpl-list.php'; }
	if ( is_singular( 'post' ) ) { return __DIR__ . '/pb-tpl-single.php'; }
	return $t;
}, 99 );


function pb_read_time( $id = null ) {
	$w = str_word_count( wp_strip_all_tags( get_post_field( 'post_content', $id ? $id : get_the_ID() ) ) );
	return max( 1, (int) ceil( $w / 220 ) ) . ' min read';
}

function pb_post_cat( $id = null ) {
	$c = get_the_category( $id ? $id : get_the_ID() );
	return $c ? $c[0] : null;
}

function pb_post_card( $big = false ) {
	$id  = get_the_ID();
	$url = get_permalink();
	$cat = pb_post_cat();
	$img = has_post_thumbnail() ? get_the_post_thumbnail( $id, 'medium_large', array( 'loading' => 'lazy', 'alt' => esc_attr( get_the_title() ) ) ) : '<span class="pb-card__ph">' . pb_ic( 'ga4' ) . '</span>';
	$o   = '<article class="pb-card">';
	$o  .= '<a class="pb-card__img" href="' . esc_url( $url ) . '" tabindex="-1" aria-hidden="true">' . $img . '</a>';
	$o  .= '<div class="pb-card__b">';
	$o  .= '<div class="pb-card__meta">' . ( $cat ? '<a class="pb-cat" href="' . esc_url( get_category_link( $cat ) ) . '">' . esc_html( $cat->name ) . '</a>' : '' ) . '<span>' . esc_html( get_the_date( 'M j, Y' ) ) . '</span></div>';
	$o  .= '<h3><a href="' . esc_url( $url ) . '">' . esc_html( get_the_title() ) . '</a></h3>';
	$o  .= '<p>' . esc_html( wp_trim_words( get_the_excerpt(), 22 ) ) . '</p>';
	$o  .= '<div class="pb-card__f"><a class="pb-link" href="' . esc_url( $url ) . '">Read Article' . pb_ic( 'arrow' ) . '</a><span>' . esc_html( pb_read_time() ) . '</span></div>';
	return $o . '</div></article>';
}

function pb_socials() {
	$l = pb_links();
	$o = '<div class="pb-soc">';
	foreach ( array( 'fiverr' => 'Fiverr', 'upwork' => 'Upwork', 'linkedin' => 'LinkedIn', 'youtube' => 'YouTube', 'facebook' => 'Facebook', 'skilluper' => 'Skilluper' ) as $k => $n ) {
		$o .= '<a href="' . esc_url( $l[ $k ] ) . '" target="_blank" rel="noopener" aria-label="' . esc_attr( $n ) . '" title="' . esc_attr( $n ) . '">' . pb_ic( $k ) . '</a>';
	}
	return $o . '</div>';
}

function pb_author_card() {
	$photo = wp_get_attachment_image( PB_PHOTO, 'medium', false, array( 'alt' => 'Bappi, Google Ads and Tracking Specialist', 'loading' => 'lazy' ) );
	return '<div class="pb-side__box pb-auth"><div class="pb-auth__ph">' . $photo . '</div><h3>Bappi</h3><p class="pb-auth__role">Google Ads &amp; Tracking Specialist</p><p class="pb-auth__bio">I set up and fix GTM, GA4, Google Ads and Meta tracking so the numbers in your ad accounts match what really happens on your site.</p><span class="pb-sig">Bappi</span>' . pb_socials() . '<a class="pb-link" href="' . esc_url( home_url( '/about/' ) ) . '">More about me' . pb_ic( 'arrow' ) . '</a></div>';
}

function pb_side_form() {
	$sent  = isset( $_GET['pb_sent'] ) ? sanitize_key( wp_unslash( $_GET['pb_sent'] ) ) : '';
	$alert = '';
	if ( '1' === $sent ) { $alert = '<div class="pb-alert ok" role="status">Thanks! I\'ll take a look and reply by email.</div>'; }
	if ( 'err' === $sent ) { $alert = '<div class="pb-alert err" role="alert">Please add your name, a valid email and a short note.</div>'; }
	$back = is_singular() ? get_permalink() : home_url( remove_query_arg( 'pb_sent', add_query_arg( array() ) ) );
	$o    = '<div class="pb-side__box pb-sform" id="contact"><span class="pb-eyebrow">Free audit</span><h3>Something not tracking?</h3><p>Tell me what is broken and I\'ll check your setup and suggest the fix.</p>' . $alert;
	$o   .= '<form method="post" action="' . esc_url( admin_url( 'admin-post.php' ) ) . '"><input type="hidden" name="action" value="pb_contact">' . wp_nonce_field( 'pb_contact', 'pb_nonce', true, false );
	$o   .= '<input type="hidden" name="pb_back" value="' . esc_attr( $back ) . '"><input type="hidden" name="service" value="tracking-audit">';
	$o   .= '<label class="hp" aria-hidden="true">Leave empty<input type="text" name="pb_hp" tabindex="-1" autocomplete="off"></label>';
	$o   .= '<input type="text" name="name" required placeholder="Your name" aria-label="Your name" autocomplete="name">';
	$o   .= '<input type="email" name="email" required placeholder="Email address" aria-label="Email address" autocomplete="email">';
	$o   .= '<input type="text" inputmode="url" name="website" placeholder="Website (e.g. yoursite.com)" aria-label="Website" autocomplete="url" autocapitalize="off" spellcheck="false">';
	$o   .= '<textarea name="message" required rows="3" placeholder="What is not tracking?" aria-label="What is not tracking?"></textarea>';
	$o   .= '<button class="pb-btn pb-btn--p" type="submit">Get a Free Tracking Audit' . pb_ic( 'arrow' ) . '</button></form></div>';
	return $o;
}

function pb_search_box() {
	return '<form class="pb-side__box pb-search" role="search" method="get" action="' . esc_url( home_url( '/' ) ) . '"><input type="search" name="s" value="' . esc_attr( get_search_query() ) . '" placeholder="Search articles" aria-label="Search articles"><input type="hidden" name="post_type" value="post"><button type="submit" aria-label="Search"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round"><circle cx="11" cy="11" r="7"/><path d="m20 20-3.5-3.5"/></svg></button></form>';
}

function pb_cat_box() {
	$cats = get_categories( array( 'hide_empty' => true, 'exclude' => array( (int) get_option( 'default_category' ) ) ) );
	if ( ! $cats ) { return ''; }
	$o = '<div class="pb-side__box"><h4>Topics</h4><ul class="pb-cats">';
	foreach ( $cats as $c ) {
		$o .= '<li><a href="' . esc_url( get_category_link( $c ) ) . '">' . esc_html( $c->name ) . '<span>' . (int) $c->count . '</span></a></li>';
	}
	return $o . '</ul></div>';
}

function pb_blog_hero() {
	$eyebrow = 'Blog &amp; resources';
	$title   = 'Notes on tracking, analytics and <span class="pb-grad">Google Ads.</span>';
	$lead    = 'Practical guides on GTM, GA4, conversion tracking and server-side setups, written from real implementation work.';
	if ( is_category() || is_tag() ) {
		$eyebrow = is_category() ? 'Topic' : 'Tag';
		$title   = esc_html( single_term_title( '', false ) );
		$d       = term_description();
		$lead    = $d ? wp_strip_all_tags( $d ) : 'All articles filed under ' . esc_html( single_term_title( '', false ) ) . '.';
	} elseif ( is_search() ) {
		$eyebrow = 'Search';
		$title   = 'Results for &ldquo;' . esc_html( get_search_query() ) . '&rdquo;';
		$lead    = '';
	} elseif ( is_author() || is_date() ) {
		$title = esc_html( wp_strip_all_tags( get_the_archive_title() ) );
		$lead  = '';
	}
	$chips = '';
	$cats  = get_categories( array( 'hide_empty' => true, 'exclude' => array( (int) get_option( 'default_category' ) ), 'number' => 8 ) );
	if ( $cats ) {
		$pf    = get_option( 'page_for_posts' );
		$chips = '<nav class="pb-topics" aria-label="Topics"><a class="' . ( is_home() ? 'on' : '' ) . '" href="' . esc_url( $pf ? get_permalink( $pf ) : home_url( '/blog/' ) ) . '">All</a>';
		foreach ( $cats as $c ) { $chips .= '<a class="' . ( is_category( $c->term_id ) ? 'on' : '' ) . '" href="' . esc_url( get_category_link( $c ) ) . '">' . esc_html( $c->name ) . '</a>'; }
		$chips .= '</nav>';
	}
	return '<section class="pb pb-bhero"><div class="pb-wrap"><span class="pb-eyebrow">' . $eyebrow . '</span><h1>' . $title . '</h1>' . ( $lead ? '<p class="pb-lead">' . $lead . '</p>' : '' ) . $chips . '</div></section>';
}

function pb_blog_render_list() {
	$l = pb_links();
	echo '<div class="pb-bpage">' . pb_blog_hero() . '<section class="pb pb-bl"><div class="pb-wrap"><div class="pb-bl__grid"><div class="pb-bl__main">'; // phpcs:ignore
	if ( have_posts() ) {
		echo '<div class="pb-cards">';
		while ( have_posts() ) { the_post(); echo pb_post_card(); } // phpcs:ignore
		echo '</div>';
		$pg = paginate_links( array( 'prev_text' => '&larr; Previous', 'next_text' => 'Next &rarr;', 'mid_size' => 1, 'type' => 'list' ) );
		if ( $pg ) { echo '<nav class="pb-pag" aria-label="Pagination">' . $pg . '</nav>'; } // phpcs:ignore
	} elseif ( is_search() ) {
		echo '<div class="pb-blog-empty"><h2>No articles matched that search.</h2><p class="pb-lead">Try a different keyword, or ask me directly about your tracking problem.</p><div class="pb-hero__btns">' . pb_btn( 'Get a Free Tracking Audit', $l['audit'] ) . '</div></div>'; // phpcs:ignore
	} else {
		echo '<div class="pb-blog-empty"><h2>The first articles are being written.</h2><p class="pb-lead">Until they are published, my YouTube channel has practical tutorials on Google Ads, GTM, GA4 and conversion tracking.</p><div class="pb-hero__btns">' . pb_btn( 'Visit My YouTube Channel', $l['yt_home'] ) . pb_btn( 'Get a Free Tracking Audit', $l['audit'], 'o' ) . '</div></div>'; // phpcs:ignore
	}
	echo '</div><aside class="pb-side">' . pb_search_box() . pb_author_card() . pb_side_form() . pb_cat_box() . '</aside></div></div></section></div>'; // phpcs:ignore
}

/* ---------- Single post ---------- */
function pb_toc_content( $html, &$toc ) {
	$toc  = array();
	$used = array();
	$html = preg_replace_callback( '#<h([23])([^>]*)>(.*?)</h\1>#is', function ( $m ) use ( &$toc, &$used ) {
		$text = trim( wp_strip_all_tags( $m[3] ) );
		if ( '' === $text ) { return $m[0]; }
		if ( preg_match( '#\sid=["\']([^"\']+)#', $m[2], $idm ) ) {
			$id = $idm[1];
			$attrs = $m[2];
		} else {
			$id = sanitize_title( $text );
			if ( ! $id ) { $id = 'section'; }
			$base = $id; $n = 2;
			while ( isset( $used[ $id ] ) ) { $id = $base . '-' . $n++; }
			$attrs = $m[2] . ' id="' . esc_attr( $id ) . '"';
		}
		$used[ $id ] = 1;
		$toc[]       = array( (int) $m[1], $id, $text );
		return '<h' . $m[1] . $attrs . '>' . $m[3] . '</h' . $m[1] . '>';
	}, $html );
	return $html;
}

function pb_toc_html( $toc, $cls ) {
	if ( count( $toc ) < 2 ) { return ''; }
	$o = '<ol>';
	foreach ( $toc as $t ) { $o .= '<li class="l' . $t[0] . '"><a href="#' . esc_attr( $t[1] ) . '">' . esc_html( $t[2] ) . '</a></li>'; }
	$o .= '</ol>';
	if ( 'm' === $cls ) { return '<details class="pb-toc pb-toc--m"><summary>On this page</summary>' . $o . '</details>'; }
	return '<nav class="pb-side__box pb-toc pb-toc--d" aria-label="On this page"><h4>On this page</h4>' . $o . '</nav>';
}

function pb_share() {
	$u = rawurlencode( get_permalink() );
	$t = rawurlencode( get_the_title() );
	return '<div class="pb-share"><span>Share</span>'
		. '<a href="https://www.linkedin.com/sharing/share-offsite/?url=' . $u . '" target="_blank" rel="noopener" aria-label="Share on LinkedIn">' . pb_ic( 'linkedin' ) . '</a>'
		. '<a href="https://www.facebook.com/sharer/sharer.php?u=' . $u . '" target="_blank" rel="noopener" aria-label="Share on Facebook">' . pb_ic( 'facebook' ) . '</a>'
		. '<a href="https://twitter.com/intent/tweet?url=' . $u . '&amp;text=' . $t . '" target="_blank" rel="noopener" aria-label="Share on X"><svg viewBox="0 0 24 24" fill="currentColor"><path d="M17.8 3h3.1l-6.8 7.7L22 21h-6.2l-4.9-6.4L5.3 21H2.2l7.2-8.3L1.8 3h6.4l4.4 5.8L17.8 3zm-1.1 16.2h1.7L7.4 4.7H5.6l11.1 14.5z"/></svg></a>'
		. '<button type="button" class="pb-copy" data-url="' . esc_attr( get_permalink() ) . '" aria-label="Copy link"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M10 14a5 5 0 0 0 7 0l3-3a5 5 0 0 0-7-7l-1 1"/><path d="M14 10a5 5 0 0 0-7 0l-3 3a5 5 0 0 0 7 7l1-1"/></svg></button></div>';
}

function pb_related( $id ) {
	$cat = pb_post_cat( $id );
	$q   = new WP_Query( array( 'post_type' => 'post', 'posts_per_page' => 3, 'post__not_in' => array( $id ), 'ignore_sticky_posts' => true, 'no_found_rows' => true, 'cat' => $cat ? $cat->term_id : 0 ) );
	if ( ! $q->have_posts() && $cat ) {
		$q = new WP_Query( array( 'post_type' => 'post', 'posts_per_page' => 3, 'post__not_in' => array( $id ), 'ignore_sticky_posts' => true, 'no_found_rows' => true ) );
	}
	if ( ! $q->have_posts() ) { return ''; }
	$o = '<section class="pb pb-sec pb-rel"><div class="pb-wrap"><div class="pb-head"><div><span class="pb-eyebrow">Keep reading</span><h2 class="pb-h2">Related Articles</h2></div></div><div class="pb-cards pb-cards--3">';
	while ( $q->have_posts() ) { $q->the_post(); $o .= pb_post_card(); }
	wp_reset_postdata();
	return $o . '</div></div></section>';
}

function pb_blog_render_single() {
	while ( have_posts() ) {
		the_post();
		$id      = get_the_ID();
		$cat     = pb_post_cat();
		$pf      = get_option( 'page_for_posts' );
		$blogurl = $pf ? get_permalink( $pf ) : home_url( '/blog/' );
		$toc     = array();
		$content = pb_toc_content( apply_filters( 'the_content', get_the_content() ), $toc );
		$upd     = get_the_modified_date( 'U' ) - get_the_date( 'U' ) > DAY_IN_SECONDS ? '<span>Updated ' . esc_html( get_the_modified_date( 'M j, Y' ) ) . '</span>' : '';
		$avatar  = wp_get_attachment_image( PB_PHOTO, 'thumbnail', false, array( 'alt' => '', 'class' => 'pb-av' ) );

		$o  = '<div class="pb-bpage pb-single"><section class="pb pb-shero"><div class="pb-wrap pb-shero__in">';
		$o .= '<nav class="pb-crumbs" aria-label="Breadcrumb"><a href="' . esc_url( home_url( '/' ) ) . '">Home</a><span>/</span><a href="' . esc_url( $blogurl ) . '">Blog</a>' . ( $cat ? '<span>/</span><a href="' . esc_url( get_category_link( $cat ) ) . '">' . esc_html( $cat->name ) . '</a>' : '' ) . '</nav>';
		$o .= ( $cat ? '<a class="pb-cat" href="' . esc_url( get_category_link( $cat ) ) . '">' . esc_html( $cat->name ) . '</a>' : '' );
		$o .= '<h1>' . esc_html( get_the_title() ) . '</h1>';
		$o .= '<div class="pb-smeta">' . $avatar . '<span><b>Bappi</b></span><span>' . esc_html( get_the_date( 'M j, Y' ) ) . '</span>' . $upd . '<span>' . esc_html( pb_read_time() ) . '</span></div>';
		$o .= '</div></section>';

		$o .= '<section class="pb pb-bl pb-bl--s"><div class="pb-wrap"><div class="pb-bl__grid"><article class="pb-art">';
		if ( has_post_thumbnail() ) { $o .= '<figure class="pb-art__img">' . get_the_post_thumbnail( $id, 'large', array( 'alt' => esc_attr( get_the_title() ) ) ) . '</figure>'; }
		$o .= pb_toc_html( $toc, 'm' );
		$o .= '<div class="pb-prose">' . $content . '</div>';
		$tags = get_the_tags();
		$o   .= '<div class="pb-art__f">';
		if ( $tags ) {
			$o .= '<div class="pb-tags">';
			foreach ( $tags as $tg ) { $o .= '<a href="' . esc_url( get_tag_link( $tg ) ) . '">#' . esc_html( $tg->name ) . '</a>'; }
			$o .= '</div>';
		}
		$o .= pb_share() . '</div>';
		$o .= '<div class="pb-abox">' . wp_get_attachment_image( PB_PHOTO, 'medium', false, array( 'alt' => 'Bappi', 'loading' => 'lazy' ) ) . '<div><span class="pb-eyebrow">Written by</span><h3>Bappi</h3><p>Google Ads and tracking specialist. I help businesses build reliable GTM, GA4, Google Ads, Meta CAPI and server-side tracking so they can see what is actually converting.</p>' . pb_socials() . '</div></div>';
		$o .= '</article><aside class="pb-side pb-side--sticky">' . pb_toc_html( $toc, 'd' ) . pb_author_card() . pb_side_form() . '</aside></div></div></section>';
		$o .= pb_related( $id );
		$o .= do_shortcode( '[pb_cta]' );
		$o .= '</div>';

		$ld = array(
			'@context'         => 'https://schema.org',
			'@type'            => 'BlogPosting',
			'headline'         => get_the_title(),
			'datePublished'    => get_the_date( 'c' ),
			'dateModified'     => get_the_modified_date( 'c' ),
			'mainEntityOfPage' => get_permalink(),
			'author'           => array( '@type' => 'Person', 'name' => 'Bappi', 'url' => home_url( '/about/' ) ),
			'publisher'        => array( '@type' => 'Person', 'name' => 'PPC BAPPI', 'url' => home_url( '/' ) ),
			'description'      => wp_trim_words( get_the_excerpt(), 30, '' ),
		);
		if ( has_post_thumbnail() ) { $ld['image'] = get_the_post_thumbnail_url( $id, 'large' ); }
		$o .= '<script type="application/ld+json">' . wp_json_encode( $ld, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE ) . '</script>';
		$o .= '<script>(function(){var l=document.querySelectorAll(".pb-toc--d a");if(!l.length||!("IntersectionObserver" in window))return;var m={};l.forEach(function(a){m[a.getAttribute("href").slice(1)]=a});var io=new IntersectionObserver(function(es){es.forEach(function(e){if(e.isIntersecting){l.forEach(function(x){x.classList.remove("on")});var a=m[e.target.id];a&&a.classList.add("on")}})},{rootMargin:"-110px 0px -70% 0px"});Object.keys(m).forEach(function(id){var h=document.getElementById(id);h&&io.observe(h)})})();</script>';
		$o .= '<script>document.addEventListener("click",function(e){var b=e.target.closest(".pb-copy");if(!b)return;navigator.clipboard&&navigator.clipboard.writeText(b.dataset.url);b.classList.add("done");setTimeout(function(){b.classList.remove("done")},1600)});</script>';
		echo $o; // phpcs:ignore
	}
}
