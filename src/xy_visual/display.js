let start_qty = MAP.ant_qty;
let end_qty = 0;
let button;
let round_nbr = 0;
let next_to_start = [];
let room_size = 36;
let	text_margin = 7;

function setup() {
	createCanvas(windowWidth, windowHeight);
	background(0, 0, 255);
	button = createButton('next');
	button.position(19, 19);
	button.mousePressed(next_round);
	button2 = createButton('reset');
	button2.position(19, 39);
	button2.mousePressed(reset);
	init_vars();
	create_links();
	init_rooms();
}

function init_vars() {
	next_to_start = MAP.rounds["1"];
}

function reset() {
	round_nbr = 0;
	end_qty = 0;
	start_qty = MAP.ant_qty;
	init_rooms();
}

function next_round() {
	round_nbr += 1;
	if (round_nbr != 0)
		draw_round();
}

function count_end_qty() {
	var count = 0;
	var round_room = MAP.rounds[round_nbr];
	for (var i = 0; i < round_room.length; i++) {
		if (MAP.rooms[round_room[i]][2] === 1)
			count += 1;
	}
	return (count);
}

function update_start_qty() {
	var round_room = MAP.rounds[round_nbr];
	if (round_room != "") {
		for (var i = 0; i < round_room.length; i++) {
			if (next_to_start.includes(round_room[i]))
				start_qty -= 1;
		}
	}
}

function draw_round() {
	var round_room = MAP.rounds[round_nbr];
	var keys_room = Object.keys(MAP.rooms);
	if (round_room) {
		for (var i = 0; i < keys_room.length; i++) {
			room = MAP.rooms[keys_room[i]];
			fill(255);
			if (round_room && round_room.includes(keys_room[i]))
				fill(0);
			if (room[2] === -1) {
				ellipse(room[0], room[1], room_size);
			}
			if (room[2] === 1) {
				fill(255, 0, 0);
				ellipse(room[0], room[1], room_size);
				if (round_room.includes(keys_room[i]))
					end_qty += count_end_qty();
				fill(0);
				text(end_qty, room[0] - text_margin, room[1] + text_margin);
			}
			if (room[2] === 0) {
				fill(0, 255, 0);
				ellipse(room[0], room[1], room_size);
				fill(0);
				update_start_qty();
				text(start_qty, room[0] - text_margin, room[1] + text_margin);
			}
		}
	}
}

function init_rooms() {
	strokeWeight(1);
	textSize(20);
	var keys_room = Object.keys(MAP.rooms);
	for (var i = 0; i < keys_room.length; i++) {
		room = MAP.rooms[keys_room[i]];
		if (room[2] === 0) {
			fill(0, 255, 0);
			ellipse(room[0], room[1], room_size);
			fill(0);
			text(start_qty, room[0] - text_margin, room[1] + text_margin);
		}
		if (room[2] === 1) {
			fill(255, 0, 0);
			ellipse(room[0], room[1], room_size);
			fill(0);
			text(end_qty, room[0] - text_margin, room[1] + text_margin);
		}
		if (room[2] === -1) {
			fill(255);
			ellipse(room[0], room[1], room_size);
		}
		fill(255);

	}
}

function create_links() {

	var keys_room = Object.keys(MAP.tunnels);
	strokeWeight(2);
	for (var i = 0; i < keys_room.length; i++) {
		var room1 = MAP.rooms[keys_room[i]];
		x1 = room1[0];
		y1 = room1[1];
		for (var j = 0; j < MAP.tunnels[keys_room[i]].length; j++) {
			var room2 = MAP.rooms[MAP.tunnels[keys_room[i]][j]];
			var x2 = room2[0];
			var y2 = room2[1];
			line(x1, y1, x2, y2);
		}
	}
}

