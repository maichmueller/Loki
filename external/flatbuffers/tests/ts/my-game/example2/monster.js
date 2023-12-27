// automatically generated by the FlatBuffers compiler, do not modify
/* eslint-disable @typescript-eslint/no-unused-vars, @typescript-eslint/no-explicit-any, @typescript-eslint/no-non-null-assertion */
import * as flatbuffers from 'flatbuffers';
export class Monster {
    constructor() {
        this.bb = null;
        this.bb_pos = 0;
    }
    __init(i, bb) {
        this.bb_pos = i;
        this.bb = bb;
        return this;
    }
    static getRootAsMonster(bb, obj) {
        return (obj || new Monster()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
    }
    static getSizePrefixedRootAsMonster(bb, obj) {
        bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
        return (obj || new Monster()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
    }
    static getFullyQualifiedName() {
        return 'MyGame.Example2.Monster';
    }
    static startMonster(builder) {
        builder.startObject(0);
    }
    static endMonster(builder) {
        const offset = builder.endObject();
        return offset;
    }
    static createMonster(builder) {
        Monster.startMonster(builder);
        return Monster.endMonster(builder);
    }
    serialize() {
        return this.bb.bytes();
    }
    static deserialize(buffer) {
        return Monster.getRootAsMonster(new flatbuffers.ByteBuffer(buffer));
    }
    unpack() {
        return new MonsterT();
    }
    unpackTo(_o) { }
}
export class MonsterT {
    constructor() { }
    pack(builder) {
        return Monster.createMonster(builder);
    }
}
