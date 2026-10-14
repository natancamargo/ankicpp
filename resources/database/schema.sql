BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "col" (
	"id"	integer,
	"crt"	integer NOT NULL,
	"mod"	integer NOT NULL,
	"scm"	integer NOT NULL,
	"ver"	integer NOT NULL,
	"dty"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"ls"	integer NOT NULL,
	"conf"	text NOT NULL,
	"models"	text NOT NULL,
	"decks"	text NOT NULL,
	"dconf"	text NOT NULL,
	"tags"	text NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "notes" (
	"id"	integer,
	"guid"	text NOT NULL,
	"mid"	integer NOT NULL,
	"mod"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"tags"	text NOT NULL,
	"flds"	text NOT NULL,
	"sfld"	integer NOT NULL,
	"csum"	integer NOT NULL,
	"flags"	integer NOT NULL,
	"data"	text NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "cards" (
	"id"	integer,
	"nid"	integer NOT NULL,
	"did"	integer NOT NULL,
	"ord"	integer NOT NULL,
	"mod"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"type"	integer NOT NULL,
	"queue"	integer NOT NULL,
	"due"	integer NOT NULL,
	"ivl"	integer NOT NULL,
	"factor"	integer NOT NULL,
	"reps"	integer NOT NULL,
	"lapses"	integer NOT NULL,
	"left"	integer NOT NULL,
	"odue"	integer NOT NULL,
	"odid"	integer NOT NULL,
	"flags"	integer NOT NULL,
	"data"	text NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "revlog" (
	"id"	integer,
	"cid"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"ease"	integer NOT NULL,
	"ivl"	integer NOT NULL,
	"lastIvl"	integer NOT NULL,
	"factor"	integer NOT NULL,
	"time"	integer NOT NULL,
	"type"	integer NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "deck_config" (
	"id"	integer NOT NULL,
	"name"	text NOT NULL ,
	"mtime_secs"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"config"	blob NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "config" (
	"KEY"	text NOT NULL,
	"usn"	integer NOT NULL,
	"mtime_secs"	integer NOT NULL,
	"val"	blob NOT NULL,
	PRIMARY KEY("KEY")
) WITHOUT ROWID;
CREATE TABLE IF NOT EXISTS "fields" (
	"ntid"	integer NOT NULL,
	"ord"	integer NOT NULL,
	"name"	text NOT NULL ,
	"config"	blob NOT NULL,
	PRIMARY KEY("ntid","ord")
) WITHOUT ROWID;
CREATE TABLE IF NOT EXISTS "templates" (
	"ntid"	integer NOT NULL,
	"ord"	integer NOT NULL,
	"name"	text NOT NULL ,
	"mtime_secs"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"config"	blob NOT NULL,
	PRIMARY KEY("ntid","ord")
) WITHOUT ROWID;
CREATE TABLE IF NOT EXISTS "notetypes" (
	"id"	integer NOT NULL,
	"name"	text NOT NULL ,
	"mtime_secs"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"config"	blob NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "decks" (
	"id"	integer NOT NULL,
	"name"	text NOT NULL ,
	"mtime_secs"	integer NOT NULL,
	"usn"	integer NOT NULL,
	"common"	blob NOT NULL,
	"kind"	blob NOT NULL,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "tags" (
	"tag"	text NOT NULL ,
	"usn"	integer NOT NULL,
	"collapsed"	boolean NOT NULL,
	"config"	blob,
	PRIMARY KEY("tag")
) WITHOUT ROWID;
CREATE TABLE IF NOT EXISTS "graves" (
	"oid"	integer NOT NULL,
	"type"	integer NOT NULL,
	"usn"	integer NOT NULL,
	PRIMARY KEY("oid","type")
) WITHOUT ROWID;
CREATE INDEX IF NOT EXISTS "ix_notes_usn" ON "notes" (
	"usn"
);
CREATE INDEX IF NOT EXISTS "ix_cards_usn" ON "cards" (
	"usn"
);
CREATE INDEX IF NOT EXISTS "ix_revlog_usn" ON "revlog" (
	"usn"
);
CREATE INDEX IF NOT EXISTS "ix_cards_nid" ON "cards" (
	"nid"
);
CREATE INDEX IF NOT EXISTS "ix_cards_sched" ON "cards" (
	"did",
	"queue",
	"due"
);
CREATE INDEX IF NOT EXISTS "ix_revlog_cid" ON "revlog" (
	"cid"
);
CREATE INDEX IF NOT EXISTS "ix_notes_csum" ON "notes" (
	"csum"
);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_fields_name_ntid" ON "fields" (
	"name",
	"ntid"
);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_templates_name_ntid" ON "templates" (
	"name",
	"ntid"
);
CREATE INDEX IF NOT EXISTS "idx_templates_usn" ON "templates" (
	"usn"
);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_notetypes_name" ON "notetypes" (
	"name"
);
CREATE INDEX IF NOT EXISTS "idx_notetypes_usn" ON "notetypes" (
	"usn"
);
CREATE UNIQUE INDEX IF NOT EXISTS "idx_decks_name" ON "decks" (
	"name"
);
CREATE INDEX IF NOT EXISTS "idx_notes_mid" ON "notes" (
	"mid"
);
CREATE INDEX IF NOT EXISTS "idx_cards_odid" ON "cards" (
	"odid"
) WHERE "odid" != 0;
CREATE INDEX IF NOT EXISTS "idx_graves_pending" ON "graves" (
	"usn"
);
COMMIT;
