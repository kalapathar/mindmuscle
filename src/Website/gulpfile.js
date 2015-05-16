//load plugins
var gulp             = require('gulp'),
	compass          = require('gulp-compass'),
	autoprefixer     = require('gulp-autoprefixer'),
	minifycss        = require('gulp-minify-css'),
	uglify           = require('gulp-uglify'),
	rename           = require('gulp-rename'),
	concat           = require('gulp-concat'),
	notify           = require('gulp-notify'),
	livereload       = require('gulp-livereload'),
	handlebars 		 = require('gulp-compile-handlebars'),
	plumber          = require('gulp-plumber'),
	minifyHTML 		 = require("gulp-minify-html"),
	rev              = require('gulp-rev'),
	debug 			 = require('gulp-debug'),
	path             = require('path'),
	fs 				 = require('fs'),
	runSequence		 = require('run-sequence'),
	gutil			 = require('gulp-util');
	
 
//the title and icon that will be used for the Grunt notifications
var notifyInfo = {
	title: 'Gulp',
	icon: path.join(__dirname, 'gulp.png')
};
 
//error notification settings for plumber
var plumberErrorHandler = { errorHandler: notify.onError({
		title: notifyInfo.title,
		icon: notifyInfo.icon,
		message: "Error: <%= error.message %>"
	})
};

// For asset version linking in handlebars templates
// create a handlebars helper to look up
// fingerprinted asset by non-fingerprinted name
var handlebarOpts = {
	batch: ['./src/templates/partials'],
	helpers: {
		assetPathCSS: function (path, context) {
			return context.data.root[path];
		},
		assetPathJS: function (path, context) {
			return 'js/' + context.data.root[path];
		},
		assetPathIMG: function (path, context) {
			return 'images/' + context.data.root[path];
		},
		assetPathFAVICON: function (path, context) {
			return context.data.root[path];
		}
	},
	ignorePartials: true // Throw an error if a partial can't be found (this is annoying)
};

// HTML Minifying
var htmlMinifyOpts = {
	conditionals: true,
	spare: true,
	quotes: true,
	empty: true
};
 
//styles
gulp.task('styles', function() {
	return gulp.src(['./src/scss/**/*.scss'])
		.pipe(plumber(plumberErrorHandler))
		.pipe(compass({
			config_file: './src/scss/config.rb',
			css: './src/scss/stylesheets',
			sass: './src/scss/sass',
			image: './public/images'
		}))
		.pipe(autoprefixer('last 2 version', 'safari 5', 'ie 7', 'ie 8', 'ie 9', 'opera 12.1', 'ios 6', 'android 4'))
		.pipe(minifycss())
		.pipe(rev())
		.pipe(rename({ suffix: '.min' }))
		.pipe(gulp.dest('./public'))
		.pipe(rev.manifest('rev-manifest-styles.json'))
		.pipe(gulp.dest('./'));
});

//scripts
gulp.task('scripts', function() {
	return gulp.src('./src/js/**/*.js')
		.pipe(plumber(plumberErrorHandler))
		//.pipe(concat('main.js'))
		.pipe(uglify())
		.pipe(rev())
		.pipe(rename({ suffix: '.min' }))
		.pipe(gulp.dest('./public/js'))
		.pipe(rev.manifest('rev-manifest-scripts.json'))
		.pipe(gulp.dest('./'));
});

//images
gulp.task('images', function() {
	return gulp.src('./src/images/**/*')
		.pipe(plumber(plumberErrorHandler))
		.pipe(rev())
		.pipe(gulp.dest('./public/images'))
		.pipe(rev.manifest('rev-manifest-images.json'))
		.pipe(gulp.dest('./'));
});

//favicons
gulp.task('favicons', function() {
	return gulp.src('./src/favicons/**/*')
		.pipe(plumber(plumberErrorHandler))
		.pipe(rev())
		.pipe(gulp.dest('./public'))
		.pipe(rev.manifest('rev-manifest-favicons.json'))
		.pipe(gulp.dest('./'));
});

//misc assets
gulp.task('assets', function() {
	return gulp.src('./src/assets/**/*')
		.pipe(plumber(plumberErrorHandler))
		.pipe(gulp.dest('./public'));
});

//various repos
gulp.task('repos', function() {
	gulp.src('./src/repos/PhotoSwipe/dist/**/*')
		.pipe(plumber(plumberErrorHandler))
		.pipe(gulp.dest('./public/libs/PhotoSwipe'));
	return true;
});

//Fonts
gulp.task('fonts', function() {
	return gulp.src('./src/fonts/**/*')
		.pipe(plumber(plumberErrorHandler))
		.pipe(gulp.dest('./public/sass'));
});

//html
gulp.task('html', function() {
	// read in our manifest file
	var templateData = {};

	try {
		var manifest = JSON.parse(fs.readFileSync('./rev-manifest-styles.json', 'utf8'));
		for (i in manifest) templateData[i] = manifest[i];
	} catch(e) {};

	try {
		var manifest = JSON.parse(fs.readFileSync('./rev-manifest-scripts.json', 'utf8'));
		for (i in manifest) templateData[i] = manifest[i];
	} catch(e) {};

	try {
		var manifest = JSON.parse(fs.readFileSync('./rev-manifest-images.json', 'utf8'));
		for (i in manifest) templateData[i] = manifest[i];
	} catch(e) {};

	try {
		var manifest = JSON.parse(fs.readFileSync('./rev-manifest-favicons.json', 'utf8'));
		for (i in manifest) templateData[i] = manifest[i];
	} catch(e) {};

	// read in our handlebars template, compile it using
	// our manifest, and output it to index.html
	return gulp.src('./src/templates/*.hbs')
		.pipe(handlebars(templateData, handlebarOpts))
		.pipe(minifyHTML(htmlMinifyOpts))
		.pipe(rename({ extname: '.html' }))
		.pipe(gulp.dest('./public'));
});
 
//watch
gulp.task('watch', function() {
	livereload.listen();
 
	//watch .scss files
	gulp.watch('./src/scss/**/*.scss', ['default']);
 
	//watch .js files
	gulp.watch('./src/js/**/*.js', ['default']);

	//watch image files
	gulp.watch('./src/images/**/*', ['default'])

	//watch asset files
	gulp.watch('./src/assets/**/*', ['default'])

	//watch .hbs files
	gulp.watch('./src/templates/**/*.hbs', ['default']);
});

//default
gulp.task('default', function(callback) {
	runSequence(['styles', 'scripts', 'images', 'favicons', 'assets', 'repos'], 'fonts', 'html', callback);
});