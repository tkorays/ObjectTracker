#ifndef TK_kvpair_H
#define TK_kvpair_H
namespace whu {
	template <typename K, typename V> class kvpair {
	public:
		K key;
		V value;
		kvpair() {

		}
		kvpair(K k, V v) {
			key = k;
			value = v;
		}
		void reset(K k, V v) {
			key = k;
			value = v;
		}
		bool operator <(const kvpair& kvp) const {
			return value < kvp.value;
		}
		bool operator >(const kvpair& kvp) const {
			return value >kvp.value;
		}
		bool operator ==(const kvpair& kvp) const {
			return equal(kvp);
		}
		bool equal(const kvpair& kvp) const{
			return (key == kvp.key) && (value == kvp.value);
		}
		bool key_equal(const kvpair& kvp) {
			return key == kvp.key;
		}
		bool value_equal(const kvpair& kvp) {
			return value == kvp.value;
		}
		double distance(const kvpair& kvp) {
			return value.distance(kvp.value);
		}
	};
}

#endif // TK_kvpair_H
