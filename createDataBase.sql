-- 启用外键约束
PRAGMA foreign_keys = ON;

-- 创建 category 表
CREATE TABLE category (
    name TEXT PRIMARY KEY,            -- 主键
    cover TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
);

-- 创建 song 表
CREATE TABLE song (
    id INTEGER PRIMARY KEY AUTOINCREMENT, -- 主键
    title TEXT,
    artist TEXT,
    album TEXT,
    duration INTEGER,
    favorite INTEGER,
    path TEXT,
    cover TEXT,
    lyric TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    UNIQUE (title, artist, album, duration, favorite, path, cover, lyric)
);

-- 创建 history 表
CREATE TABLE history (
    song_id INTEGER,                     -- 外键，引用 song(id)
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    FOREIGN KEY (song_id) REFERENCES song(id) ON DELETE CASCADE
);

-- 创建 playList 表
CREATE TABLE playList (
    song_id INTEGER,                     -- 外键，引用 song(id)
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,
    FOREIGN KEY (song_id) REFERENCES song(id) ON DELETE CASCADE
);

-- 创建 songCategoryRelations 表
CREATE TABLE songCategoryRelationship (
    song_id INTEGER,                     -- 外键，引用 song(id)
    category_name TEXT,                  -- 外键，引用 category(name)
    FOREIGN KEY (song_id) REFERENCES song(id) ON DELETE CASCADE,
    FOREIGN KEY (category_name) REFERENCES category(name) ON DELETE CASCADE
);