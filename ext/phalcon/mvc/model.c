
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Mvc\Model
 *
 * <p>Phalcon\Mvc\Model connects business objects and database tables to create
 * a persistable domain model where logic and data are presented in one wrapping.
 * It‘s an implementation of the object-relational mapping (ORM).</p>
 *
 * <p>A model represents the information (data) of the application and the rules to manipulate that data.
 * Models are primarily used for managing the rules of interaction with a corresponding database table.
 * In most cases, each table in your database will correspond to one model in your application.
 * The bulk of your application’s business logic will be concentrated in the models.</p>
 *
 * <p>Phalcon\Mvc\Model is the first ORM written in C-language for PHP, giving to developers high performance
 * when interacting with databases while is also easy to use.</p>
 *
 * <code>
 *
 * $robot = new Robots();
 * $robot->type = 'mechanical';
 * $robot->name = 'Astro Boy';
 * $robot->year = 1952;
 * if ($robot->save() == false) {
 *  echo "Umh, We can store robots: ";
 *  foreach ($robot->getMessages() as $message) {
 *    echo message;
 *  }
 * } else {
 *  echo "Great, a new robot was saved successfully!";
 * }
 * </code>
 *
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc, Model, phalcon, mvc_model, phalcon_mvc_model_method_entry, 0);

	zend_declare_property_null(phalcon_mvc_model_ce, SL("_dependencyInjector"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_modelsManager"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_modelsMetaData"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_errorMessages"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(phalcon_mvc_model_ce, SL("_operationMade"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_long(phalcon_mvc_model_ce, SL("_dirtyState"), 1, ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_transaction"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_uniqueKey"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_uniqueParams"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_uniqueTypes"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_skipped"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_related"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(phalcon_mvc_model_ce, SL("_snapshot"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_NONE"), 0 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_CREATE"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_UPDATE"), 2 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("OP_DELETE"), 3 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_PERSISTENT"), 0 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_TRANSIENT"), 1 TSRMLS_CC);
	zend_declare_class_constant_long(phalcon_mvc_model_ce, SL("DIRTY_STATE_DETACHED"), 2 TSRMLS_CC);

	return SUCCESS;

}

/**
 * Phalcon\Mvc\Model constructor
 *
 * @param Phalcon\DiInterface dependencyInjector
 * @param Phalcon\Mvc\Model\ManagerInterface modelsManager
 */
PHP_METHOD(Phalcon_Mvc_Model, __construct) {

	zval *dependencyInjector = NULL, *modelsManager = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &dependencyInjector, &modelsManager);

	if (!dependencyInjector) {
		ZEPHIR_CPY_WRT(dependencyInjector, ZEPHIR_GLOBAL(global_null));
	}
	ZEPHIR_SEPARATE_PARAM(dependencyInjector);
	if (!modelsManager) {
		ZEPHIR_CPY_WRT(modelsManager, ZEPHIR_GLOBAL(global_null));
	}
	ZEPHIR_SEPARATE_PARAM(modelsManager);


	if ((Z_TYPE_P(dependencyInjector) != IS_OBJECT)) {
		ZEPHIR_INIT_NVAR(dependencyInjector);
		zephir_call_static(dependencyInjector, "Phalcon\\Di", "getdefault");
	}
	if ((Z_TYPE_P(dependencyInjector) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "A dependency injector container is required to obtain the services related to the ORM");
		return;
	}
	zephir_update_property_this(this_ptr, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);
	if ((Z_TYPE_P(modelsManager) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "modelsManager", 1);
		zephir_call_method_p1(_0, dependencyInjector, "getshared", _1);
		ZEPHIR_CPY_WRT(modelsManager, _0);
		if ((Z_TYPE_P(modelsManager) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The injected service 'modelsManager' is not valid");
			return;
		}
	}
	zephir_update_property_this(this_ptr, SL("_modelsManager"), modelsManager TSRMLS_CC);
	zephir_call_method_p1_noret(modelsManager, "initialize", this_ptr);
	if ((zephir_method_exists_str(this_ptr, SS("onconstruct") TSRMLS_CC) == SUCCESS)) {
		zephir_call_method_noret(this_ptr, "onconstruct");
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the dependency injection container
 *
 * @param Phalcon\DiInterface dependencyInjector
 */
PHP_METHOD(Phalcon_Mvc_Model, setDI) {

	zval *dependencyInjector;

	zephir_fetch_params(0, 1, 0, &dependencyInjector);



	zephir_update_property_this(this_ptr, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);

}

/**
 * Returns the dependency injection container
 *
 * @return Phalcon\DiInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getDI) {


	RETURN_MEMBER(this_ptr, "_dependencyInjector");

}

/**
 * Sets a custom events manager
 *
 * @param Phalcon\Events\ManagerInterface eventsManager
 */
PHP_METHOD(Phalcon_Mvc_Model, setEventsManager) {

	zval *eventsManager, *modelsManager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &eventsManager);



	modelsManager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p2_noret(modelsManager, "setcustomeventsmanager", this_ptr, eventsManager);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the custom events manager
 *
 * @return Phalcon\Events\ManagerInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getEventsManager) {

	zval *modelsManager;

	ZEPHIR_MM_GROW();

	modelsManager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p1(return_value, modelsManager, "getcustomeventsmanager", this_ptr);
	RETURN_MM();

}

/**
 * Returns the models meta-data service related to the entity instance
 *
 * @return Phalcon\Mvc\Model\MetaDataInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getModelsMetaData) {

	zval *metaData = NULL, *dependencyInjector = NULL, *_0, *_1, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(metaData);
	zephir_read_property_this(&metaData, this_ptr, SL("_modelsMetaData"), PH_NOISY_CC);
	if ((Z_TYPE_P(metaData) != IS_OBJECT)) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dependencyInjector"), PH_NOISY_CC);
		ZEPHIR_CPY_WRT(dependencyInjector, _0);
		if ((Z_TYPE_P(dependencyInjector) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "A dependency injector container is required to obtain the services related to the ORM");
			return;
		}
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "modelsMetadata", 1);
		zephir_call_method_p1(_1, dependencyInjector, "getshared", _2);
		ZEPHIR_CPY_WRT(metaData, _1);
		if ((Z_TYPE_P(metaData) != IS_OBJECT)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The injected service 'modelsMetadata' is not valid");
			return;
		}
		zephir_update_property_this(this_ptr, SL("_modelsMetaData"), metaData TSRMLS_CC);
	}
	RETURN_CCTOR(metaData);

}

/**
 * Returns the models manager related to the entity instance
 *
 * @return Phalcon\Mvc\Model\ManagerInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getModelsManager) {


	RETURN_MEMBER(this_ptr, "_modelsManager");

}

/**
 * Sets a transaction related to the Model instance
 *
 *<code>
 *use Phalcon\Mvc\Model\Transaction\Manager as TxManager;
 *use Phalcon\Mvc\Model\Transaction\Failed as TxFailed;
 *
 *try {
 *
 *  $txManager = new TxManager();
 *
 *  $transaction = $txManager->get();
 *
 *  $robot = new Robots();
 *  $robot->setTransaction($transaction);
 *  $robot->name = 'WALL·E';
 *  $robot->created_at = date('Y-m-d');
 *  if ($robot->save() == false) {
 *    $transaction->rollback("Can't save robot");
 *  }
 *
 *  $robotPart = new RobotParts();
 *  $robotPart->setTransaction($transaction);
 *  $robotPart->type = 'head';
 *  if ($robotPart->save() == false) {
 *    $transaction->rollback("Robot part cannot be saved");
 *  }
 *
 *  $transaction->commit();
 *
 *} catch (TxFailed $e) {
 *  echo 'Failed, reason: ', $e->getMessage();
 *}
 *
 *</code>
 *
 * @param Phalcon\Mvc\Model\TransactionInterface $transaction
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setTransaction) {

	zval *transaction;

	zephir_fetch_params(0, 1, 0, &transaction);



	if ((Z_TYPE_P(transaction) == IS_OBJECT)) {
		zephir_update_property_this(this_ptr, SL("_transaction"), transaction TSRMLS_CC);
		RETURN_THISW();
	}
	ZEPHIR_THROW_EXCEPTION_STRW(phalcon_mvc_model_exception_ce, "Transaction should be an object");
	return;

}

/**
 * Sets table name which model should be mapped
 *
 * @param string source
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setSource) {

	zval *source_param = NULL, *modelsManager;
	zval *source = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &source_param);

		zephir_get_strval(source, source_param);


	modelsManager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p2_noret(modelsManager, "setmodelsource", this_ptr, source);
	RETURN_THIS();

}

/**
 * Returns table name mapped in the model
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model, getSource) {

	zval *modelsManager = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getmodelsource", this_ptr);
	RETURN_MM();

}

/**
 * Sets schema name where table mapped is located
 *
 * @param string schema
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setSchema) {

	zval *schema_param = NULL, *modelsManager = NULL, *_0;
	zval *schema = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &schema_param);

		zephir_get_strval(schema, schema_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p2_noret(modelsManager, "setmodelschema", this_ptr, schema);
	RETURN_THIS();

}

/**
 * Returns schema name where table mapped is located
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model, getSchema) {

	zval *modelsManager = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getmodelschema", this_ptr);
	RETURN_MM();

}

/**
 * Sets the DependencyInjection connection service name
 *
 * @param string connectionService
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setConnectionService) {

	zval *connectionService_param = NULL, *modelsManager = NULL, *_0;
	zval *connectionService = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &connectionService_param);

		zephir_get_strval(connectionService, connectionService_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p2_noret(modelsManager, "setconnectionservice", this_ptr, connectionService);
	RETURN_THIS();

}

/**
 * Sets the DependencyInjection connection service name used to read data
 *
 * @param string connectionService
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setReadConnectionService) {

	zval *connectionService_param = NULL, *modelsManager = NULL, *_0;
	zval *connectionService = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &connectionService_param);

		zephir_get_strval(connectionService, connectionService_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p2_noret(modelsManager, "setreadconnectionservice", this_ptr, connectionService);
	RETURN_THIS();

}

/**
 * Sets the DependencyInjection connection service name used to write data
 *
 * @param string connectionService
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setWriteConnectionService) {

	zval *connectionService_param = NULL, *modelsManager = NULL, *_0;
	zval *connectionService = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &connectionService_param);

		zephir_get_strval(connectionService, connectionService_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p2_noret(modelsManager, "setwriteconnectionservice", this_ptr, connectionService);
	RETURN_THIS();

}

/**
 * Returns the DependencyInjection connection service name used to read data related the model
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model, getReadConnectionService) {

	zval *modelsManager = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getreadconnectionservice", this_ptr);
	RETURN_MM();

}

/**
 * Returns the DependencyInjection connection service name used to write data related to the model
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model, getWriteConnectionService) {

	zval *modelsManager = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getwriteconnectionservice", this_ptr);
	RETURN_MM();

}

/**
 * Sets the dirty state of the object using one of the DIRTY_STATE_* constants
 *
 * @param int dirtyState
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, setDirtyState) {

	zval *dirtyState_param = NULL, *_0;
	int dirtyState;

	zephir_fetch_params(0, 1, 0, &dirtyState_param);

		dirtyState = zephir_get_intval(dirtyState_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, dirtyState);
	zephir_update_property_zval(this_ptr, SL("_dirtyState"), _0 TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Returns one of the DIRTY_STATE_* constants telling if the record exists in the database or not
 *
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model, getDirtyState) {


	RETURN_MEMBER(this_ptr, "_dirtyState");

}

/**
 * Gets the connection used to read data for the model
 *
 * @return Phalcon\Db\AdapterInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getReadConnection) {

	zval *modelsManager = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getreadconnection", this_ptr);
	RETURN_MM();

}

/**
 * Gets the connection used to write data to the model
 *
 * @return Phalcon\Db\AdapterInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getWriteConnection) {

	zval *modelsManager = NULL, *transaction = NULL, *_0;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_transaction"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(transaction, _0);
	if ((Z_TYPE_P(transaction) == IS_OBJECT)) {
		zephir_call_method(return_value, transaction, "getconnection");
		RETURN_MM();
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p1(return_value, modelsManager, "getwriteconnection", this_ptr);
	RETURN_MM();

}

/**
 * Assigns values to a model from an array
 *
 *<code>
 *$robot->assign(array(
 *  'type' => 'mechanical',
 *  'name' => 'Astro Boy',
 *  'year' => 1952
 *));
 *</code>
 *
 * @param Phalcon\Mvc\Model object
 * @param array data
 * @param array columnMap
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, assign) {

	zend_function *_6 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *data, *columnMap = NULL, *key = NULL, *value = NULL, *attribute = NULL, **_2, *_3 = NULL, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &data, &columnMap);

	if (!columnMap) {
		ZEPHIR_CPY_WRT(columnMap, ZEPHIR_GLOBAL(global_null));
	}


	if ((Z_TYPE_P(data) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data to dump in the object must be an Array");
		return;
	}
	zephir_is_iterable(data, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
			ZEPHIR_OBS_NVAR(attribute);
			if (zephir_array_isset_fetch(&attribute, columnMap, key TSRMLS_CC)) {
				zephir_update_property_zval_zval(this_ptr, attribute, value TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(_3);
				object_init_ex(_3, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_SV(_4, "Column '", key);
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_VS(_5, _4, "' doesn\'t make part of the column map");
				zephir_call_method_p1_cache_noret(_3, "__construct", &_6, _5);
				zephir_throw_exception(_3 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			zephir_update_property_zval_zval(this_ptr, key, value TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Assigns values to a model from an array returning a new model.
 *
 *<code>
 *$robot = \Phalcon\Mvc\Model::cloneResultMap(new Robots(), array(
 *  'type' => 'mechanical',
 *  'name' => 'Astro Boy',
 *  'year' => 1952
 *));
 *</code>
 *
 * @param Phalcon\Mvc\Model base
 * @param array data
 * @param array columnMap
 * @param int dirtyState
 * @param boolean keepSnapshots
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResultMap) {

	zend_function *_6 = NULL;
	HashTable *_2;
	HashPosition _1;
	zend_bool keepSnapshots;
	int dirtyState;
	zval *base, *data, *columnMap, *dirtyState_param = NULL, *keepSnapshots_param = NULL, *object, *attribute = NULL, *key = NULL, *value = NULL, *_0 = NULL, **_3, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 2, &base, &data, &columnMap, &dirtyState_param, &keepSnapshots_param);

	if (!dirtyState_param) {
		dirtyState = 0;	} else {
		dirtyState = zephir_get_intval(dirtyState_param);
	}
	if (!keepSnapshots_param) {
		keepSnapshots = 0;
	} else {
		keepSnapshots = zephir_get_boolval(keepSnapshots_param);
	}


	if ((Z_TYPE_P(data) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data to dump in the object must be an Array");
		return;
	}
	ZEPHIR_INIT_VAR(object);
	ZVAL_NULL(object);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, dirtyState);
	zephir_call_method_p1_noret(object, "setdirtystate", _0);
	zephir_is_iterable(data, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		if ((Z_TYPE_P(key) == IS_STRING)) {
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attribute);
				if (zephir_array_isset_fetch(&attribute, columnMap, key TSRMLS_CC)) {
					zephir_update_property_zval_zval(object, attribute, value TSRMLS_CC);
				} else {
					ZEPHIR_INIT_NVAR(_0);
					object_init_ex(_0, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_4);
					ZEPHIR_CONCAT_SV(_4, "Column '", key);
					ZEPHIR_INIT_LNVAR(_5);
					ZEPHIR_CONCAT_VS(_5, _4, "' doesn't make part of the column map");
					zephir_call_method_p1_cache_noret(_0, "__construct", &_6, _5);
					zephir_throw_exception(_0 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				zephir_update_property_zval_zval(object, key, value TSRMLS_CC);
			}
		}
	}
	if (keepSnapshots) {
		zephir_call_method_p2_noret(object, "setsnapshotdata", data, columnMap);
	}
	if ((zephir_method_exists_str(object, SS("afterfetch") TSRMLS_CC) == SUCCESS)) {
		zephir_call_method_noret(object, "afterfetch");
	}
	RETURN_CCTOR(object);

}

/**
 * Returns an hydrated result based on the data and the column map
 *
 * @param array data
 * @param array columnMap
 * @param int hydrationMode
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResultMapHydrate) {

	zend_function *_6 = NULL;
	HashTable *_1;
	HashPosition _0;
	int hydrationMode;
	zval *data, *columnMap, *hydrationMode_param = NULL, *hydrate, *key = NULL, *value = NULL, *attribute = NULL, **_2, *_3 = NULL, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &data, &columnMap, &hydrationMode_param);

		hydrationMode = zephir_get_intval(hydrationMode_param);


	if ((Z_TYPE_P(data) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data to hidrate must be an Array");
		return;
	}
	if ((Z_TYPE_P(columnMap) != IS_ARRAY)) {
		if ((hydrationMode == 1)) {
			RETURN_CCTOR(data);
		}
	}
	ZEPHIR_INIT_VAR(hydrate);
	if ((hydrationMode == 1)) {
		array_init(hydrate);
	} else {
		object_init(hydrate);
	}
	zephir_is_iterable(data, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if ((Z_TYPE_P(key) == IS_STRING)) {
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attribute);
				if (!(zephir_array_isset_fetch(&attribute, columnMap, key TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_3);
					object_init_ex(_3, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_4);
					ZEPHIR_CONCAT_SV(_4, "Column '", key);
					ZEPHIR_INIT_LNVAR(_5);
					ZEPHIR_CONCAT_VS(_5, _4, "' doesn't make part of the column map");
					zephir_call_method_p1_cache_noret(_3, "__construct", &_6, _5);
					zephir_throw_exception(_3 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				if ((hydrationMode == 1)) {
					zephir_array_update_zval(&hydrate, attribute, &value, PH_COPY | PH_SEPARATE);
				} else {
					zephir_update_property_zval_zval(hydrate, attribute, value TSRMLS_CC);
				}
			} else {
				if ((hydrationMode == 1)) {
					zephir_array_update_zval(&hydrate, key, &value, PH_COPY | PH_SEPARATE);
				} else {
					zephir_update_property_zval_zval(hydrate, key, value TSRMLS_CC);
				}
			}
		}
	}
	RETURN_CCTOR(hydrate);

}

/**
 * Assigns values to a model from an array returning a new model
 *
 *<code>
 *$robot = Phalcon\Mvc\Model::cloneResult(new Robots(), array(
 *  'type' => 'mechanical',
 *  'name' => 'Astro Boy',
 *  'year' => 1952
 *));
 *</code>
 *
 * @param Phalcon\Mvc\Model $base
 * @param array data
 * @param int dirtyState
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, cloneResult) {

	HashTable *_2;
	HashPosition _1;
	int dirtyState;
	zval *base, *data, *dirtyState_param = NULL, *object, *key = NULL, *value = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &base, &data, &dirtyState_param);

	if (!dirtyState_param) {
		dirtyState = 0;	} else {
		dirtyState = zephir_get_intval(dirtyState_param);
	}


	if ((Z_TYPE_P(data) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data to dump in the object must be an Array");
		return;
	}
	ZEPHIR_INIT_VAR(object);
	ZVAL_NULL(object);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, dirtyState);
	zephir_call_method_p1_noret(object, "setdirtystate", _0);
	zephir_is_iterable(data, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		if ((Z_TYPE_P(key) != IS_STRING)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Invalid key in array data provided to dumpResult()");
			return;
		}
		zephir_update_property_zval_zval(object, key, value TSRMLS_CC);
	}
	if ((zephir_method_exists_str(object, SS("afterfetch") TSRMLS_CC) == SUCCESS)) {
		zephir_call_method_noret(object, "afterfetch");
	}
	RETURN_CCTOR(object);

}

/**
 * Allows to query a set of records that match the specified conditions
 *
 * <code>
 *
 * //How many robots are there?
 * $robots = Robots::find();
 * echo "There are ", count($robots), "\n";
 *
 * //How many mechanical robots are there?
 * $robots = Robots::find("type='mechanical'");
 * echo "There are ", count($robots), "\n";
 *
 * //Get and print virtual robots ordered by name
 * $robots = Robots::find(array("type='virtual'", "order" => "name"));
 * foreach ($robots as $robot) {
 *	   echo $robot->name, "\n";
 * }
 *
 * //Get first 100 virtual robots ordered by name
 * $robots = Robots::find(array("type='virtual'", "order" => "name", "limit" => 100));
 * foreach ($robots as $robot) {
 *	   echo $robot->name, "\n";
 * }
 * </code>
 *
 * @param 	array parameters
 * @return  Phalcon\Mvc\Model\ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, find) {

	zval *parameters = NULL, *params = NULL, *builder, *query, *bindParams = NULL, *bindTypes = NULL, *cache, *resultset, *hydration, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	if ((Z_TYPE_P(parameters) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
		if ((Z_TYPE_P(parameters) != IS_NULL)) {
			zephir_array_append(&params, parameters, PH_SEPARATE);
		}
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_INIT_VAR(builder);
	object_init_ex(builder, phalcon_mvc_model_query_builder_ce);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_func(_0, "get_called_class");
	zephir_call_method_p1_noret(builder, "from", _0);
	ZEPHIR_INIT_VAR(query);
	zephir_call_method(query, builder, "getquery");
	ZEPHIR_INIT_VAR(bindParams);
	ZVAL_NULL(bindParams);
	ZEPHIR_INIT_VAR(bindTypes);
	ZVAL_NULL(bindTypes);
	ZEPHIR_OBS_NVAR(bindParams);
	if (zephir_array_isset_string_fetch(&bindParams, params, SS("bind") TSRMLS_CC)) {
		ZEPHIR_OBS_NVAR(bindTypes);
	}
	ZEPHIR_OBS_VAR(cache);
	if (zephir_array_isset_string_fetch(&cache, params, SS("cache") TSRMLS_CC)) {
		zephir_call_method_p1_noret(query, "cache", cache);
	}
	ZEPHIR_INIT_VAR(resultset);
	zephir_call_method_p2(resultset, query, "execute", bindParams, bindTypes);
	if ((Z_TYPE_P(resultset) == IS_OBJECT)) {
		ZEPHIR_OBS_VAR(hydration);
		if (zephir_array_isset_string_fetch(&hydration, params, SS("hydration") TSRMLS_CC)) {
			zephir_call_method_p1_noret(resultset, "sethydratemode", hydration);
		}
	}
	RETURN_CCTOR(resultset);

}

/**
 * Allows to query the first record that match the specified conditions
 *
 * <code>
 *
 * //What's the first robot in robots table?
 * $robot = Robots::findFirst();
 * echo "The robot name is ", $robot->name;
 *
 * //What's the first mechanical robot in robots table?
 * $robot = Robots::findFirst("type='mechanical'");
 * echo "The first mechanical robot name is ", $robot->name;
 *
 * //Get first virtual robot ordered by name
 * $robot = Robots::findFirst(array("type='virtual'", "order" => "name"));
 * echo "The first virtual robot name is ", $robot->name;
 *
 * </code>
 *
 * @param array parameters
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, findFirst) {

	zval *parameters = NULL, *params = NULL, *builder, *query, *bindParams = NULL, *bindTypes = NULL, *cache, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	if ((Z_TYPE_P(parameters) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
		if ((Z_TYPE_P(parameters) != IS_NULL)) {
			zephir_array_append(&params, parameters, PH_SEPARATE);
		}
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_INIT_VAR(builder);
	object_init_ex(builder, phalcon_mvc_model_query_builder_ce);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_func(_0, "get_called_class");
	zephir_call_method_p1_noret(builder, "from", _0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 1);
	zephir_call_method_p1_noret(builder, "limit", _1);
	ZEPHIR_INIT_VAR(query);
	zephir_call_method(query, builder, "getquery");
	ZEPHIR_INIT_VAR(bindParams);
	ZVAL_NULL(bindParams);
	ZEPHIR_INIT_VAR(bindTypes);
	ZVAL_NULL(bindTypes);
	ZEPHIR_OBS_NVAR(bindParams);
	if (zephir_array_isset_string_fetch(&bindParams, params, SS("bind") TSRMLS_CC)) {
		ZEPHIR_OBS_NVAR(bindTypes);
	}
	ZEPHIR_OBS_VAR(cache);
	if (zephir_array_isset_string_fetch(&cache, params, SS("cache") TSRMLS_CC)) {
		zephir_call_method_p1_noret(query, "cache", cache);
	}
	zephir_call_method_p1_noret(query, "setuniquerow", ZEPHIR_GLOBAL(global_true));
	zephir_call_method_p2(return_value, query, "execute", bindParams, bindTypes);
	RETURN_MM();

}

/**
 * Create a criteria for a specific model
 *
 * @param Phalcon\DiInterface dependencyInjector
 * @return Phalcon\Mvc\Model\Criteria
 */
PHP_METHOD(Phalcon_Mvc_Model, query) {

	zval *dependencyInjector = NULL, *criteria, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &dependencyInjector);

	if (!dependencyInjector) {
		ZEPHIR_CPY_WRT(dependencyInjector, ZEPHIR_GLOBAL(global_null));
	}
	ZEPHIR_SEPARATE_PARAM(dependencyInjector);


	if ((Z_TYPE_P(dependencyInjector) != IS_OBJECT)) {
		ZEPHIR_INIT_NVAR(dependencyInjector);
		zephir_call_static(dependencyInjector, "Phalcon\\Di", "getdefault");
	}
	ZEPHIR_INIT_VAR(criteria);
	object_init_ex(criteria, phalcon_mvc_model_criteria_ce);
	zephir_call_method_p1_noret(criteria, "setdi", dependencyInjector);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_func(_0, "get_called_class");
	zephir_call_method_p1_noret(criteria, "setmodelname", _0);
	RETURN_CCTOR(criteria);

}

/**
 * Checks if the current record already exists or not
 *
 * @param Phalcon\Mvc\Model\MetadataInterface metaData
 * @param Phalcon\Db\AdapterInterface connection
 * @param string|array table
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _exists) {

	zend_function *_7 = NULL, *_8 = NULL, *_9 = NULL;
	HashTable *_3;
	HashPosition _2;
	int numberEmpty, numberPrimary;
	zval *metaData, *connection, *table = NULL, *uniqueParams = NULL, *uniqueTypes = NULL, *uniqueKey = NULL, *columnMap, *primaryKeys, *wherePk, *field = NULL, *attributeField = NULL, *value = NULL, *bindDataTypes, *joinWhere, *num, *type = NULL, *schema, *source, *_0 = NULL, *_1, **_4, *_5 = NULL, *_6 = NULL, *_10 = NULL, _11, *_12, *_13, *_14, *_15, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &metaData, &connection, &table);

	if (!table) {
		ZEPHIR_CPY_WRT(table, ZEPHIR_GLOBAL(global_null));
	}
	ZEPHIR_SEPARATE_PARAM(table);


	ZEPHIR_INIT_VAR(uniqueParams);
	ZVAL_NULL(uniqueParams);
	ZEPHIR_INIT_VAR(uniqueTypes);
	ZVAL_NULL(uniqueTypes);
	ZEPHIR_OBS_VAR(uniqueKey);
	zephir_read_property_this(&uniqueKey, this_ptr, SL("_uniqueKey"), PH_NOISY_CC);
	if ((Z_TYPE_P(uniqueKey) == IS_NULL)) {
		ZEPHIR_INIT_VAR(primaryKeys);
		zephir_call_method_p1(primaryKeys, metaData, "getprimarykeyattributes", this_ptr);
		ZEPHIR_INIT_VAR(bindDataTypes);
		zephir_call_method_p1(bindDataTypes, metaData, "getbindtypes", this_ptr);
		numberPrimary = zephir_fast_count_int(primaryKeys TSRMLS_CC);
		if (!(numberPrimary)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_VAR(columnMap);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "orm.column_renaming", 1);
		ZEPHIR_INIT_VAR(_1);
		zephir_call_func_p1(_1, "globals_get", _0);
		if (zephir_is_true(_1)) {
			zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
		} else {
			ZVAL_NULL(columnMap);
		}
		numberEmpty = 0;
		ZEPHIR_INIT_VAR(wherePk);
		array_init(wherePk);
		ZEPHIR_INIT_BNVAR(uniqueParams);
		array_init(uniqueParams);
		ZEPHIR_INIT_BNVAR(uniqueTypes);
		array_init(uniqueTypes);
		zephir_is_iterable(primaryKeys, &_3, &_2, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
			; zend_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(field, _4);
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, field TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_0);
					object_init_ex(_0, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_5);
					ZEPHIR_CONCAT_SV(_5, "Column '", field);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_VS(_6, _5, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_0, "__construct", &_7, _6);
					zephir_throw_exception(_0 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, field);
			}
			ZEPHIR_INIT_NVAR(value);
			ZVAL_NULL(value);
			if (1) {
				if (0) {
					numberEmpty++;
				}
				zephir_array_append(&uniqueParams, value, PH_SEPARATE);
			} else {
				zephir_array_append(&uniqueParams, ZEPHIR_GLOBAL(global_null), PH_SEPARATE);
				numberEmpty++;
			}
			ZEPHIR_OBS_NVAR(type);
			if (!(zephir_array_isset_fetch(&type, bindDataTypes, field TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_0);
				object_init_ex(_0, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_SV(_5, "Column '", field);
				ZEPHIR_INIT_LNVAR(_6);
				ZEPHIR_CONCAT_VS(_6, _5, "' isn't part of the table columns");
				zephir_call_method_p1_cache_noret(_0, "__construct", &_8, _6);
				zephir_throw_exception(_0 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_append(&uniqueTypes, type, PH_SEPARATE);
			ZEPHIR_INIT_NVAR(_0);
			zephir_call_method_p1_cache(_0, connection, "escapeidentifier", &_9, field);
			ZEPHIR_INIT_LNVAR(_10);
			ZEPHIR_CONCAT_VS(_10, _0, " = ?");
			zephir_array_append(&wherePk, _10, PH_SEPARATE);
		}
		if ((numberPrimary == numberEmpty)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_SINIT_VAR(_11);
		ZVAL_STRING(&_11, " AND ", 0);
		ZEPHIR_INIT_VAR(joinWhere);
		zephir_call_func_p2(joinWhere, "join", &_11, wherePk);
		zephir_update_property_this(this_ptr, SL("_uniqueKey"), joinWhere TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_uniqueParams"), uniqueParams TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_uniqueTypes"), uniqueTypes TSRMLS_CC);
		ZEPHIR_CPY_WRT(uniqueKey, joinWhere);
	}
	_12 = zephir_fetch_nproperty_this(this_ptr, SL("_dirtyState"), PH_NOISY_CC);
	if (!(zephir_is_true(_12))) {
		RETURN_MM_BOOL(1);
	}
	if ((Z_TYPE_P(uniqueKey) == IS_NULL)) {
		ZEPHIR_OBS_NVAR(uniqueKey);
		zephir_read_property_this(&uniqueKey, this_ptr, SL("_uniqueKey"), PH_NOISY_CC);
	}
	if ((Z_TYPE_P(uniqueParams) == IS_NULL)) {
		ZEPHIR_OBS_NVAR(uniqueParams);
		zephir_read_property_this(&uniqueParams, this_ptr, SL("_uniqueParams"), PH_NOISY_CC);
	}
	if ((Z_TYPE_P(uniqueTypes) == IS_NULL)) {
		ZEPHIR_OBS_NVAR(uniqueTypes);
		zephir_read_property_this(&uniqueTypes, this_ptr, SL("_uniqueTypes"), PH_NOISY_CC);
	}
	ZEPHIR_INIT_VAR(schema);
	zephir_call_method(schema, this_ptr, "getschema");
	ZEPHIR_INIT_VAR(source);
	zephir_call_method(source, this_ptr, "getsource");
	if (zephir_is_true(schema)) {
		ZEPHIR_INIT_NVAR(table);
		array_init(table);
		zephir_array_append(&table, schema, 0);
		zephir_array_append(&table, source, 0);
	} else {
		ZEPHIR_CPY_WRT(table, source);
	}
	ZEPHIR_INIT_NVAR(_0);
	zephir_call_method_p1(_0, connection, "escapeidentifier", table);
	ZEPHIR_INIT_LNVAR(_10);
	ZEPHIR_CONCAT_SV(_10, "SELECT COUNT(*) \"rowcount\" FROM ", _0);
	ZEPHIR_INIT_VAR(_13);
	ZEPHIR_CONCAT_VS(_13, _10, " WHERE ");
	ZEPHIR_INIT_VAR(_14);
	concat_function(_14, _13, uniqueKey TSRMLS_CC);
	ZEPHIR_INIT_VAR(num);
	zephir_call_method_p4(num, connection, "fetchone", _14, ZEPHIR_GLOBAL(global_null), uniqueParams, uniqueTypes);
	zephir_array_fetch_string(&_15, num, SL("rowcount"), PH_NOISY | PH_READONLY TSRMLS_CC);
	if (zephir_is_true(_15)) {
		ZEPHIR_INIT_ZVAL_NREF(_16);
		ZVAL_LONG(_16, 0);
		zephir_update_property_this(this_ptr, SL("_dirtyState"), _16 TSRMLS_CC);
		RETURN_MM_BOOL(1);
	} else {
		ZEPHIR_INIT_ZVAL_NREF(_16);
		ZVAL_LONG(_16, 1);
		zephir_update_property_this(this_ptr, SL("_dirtyState"), _16 TSRMLS_CC);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Generate a PHQL SELECT statement for an aggregate
 *
 * @param string function
 * @param string alias
 * @param array parameters
 * @return Phalcon\Mvc\Model\ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, _groupResult) {

	zval *functionName_param = NULL, *alias_param = NULL, *parameters, *params = NULL, *distinctColumn, *groupColumn, *columns = NULL, *bindParams = NULL, *bindTypes = NULL, *resultset, *cache, *firstRow, *groupColumns, *builder, *query, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_5, *_6;
	zval *functionName = NULL, *alias = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &functionName_param, &alias_param, &parameters);

		zephir_get_strval(functionName, functionName_param);
		zephir_get_strval(alias, alias_param);


	if ((Z_TYPE_P(parameters) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(params);
		array_init(params);
		if ((Z_TYPE_P(parameters) != IS_NULL)) {
			zephir_array_append(&params, parameters, PH_SEPARATE);
		}
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_OBS_VAR(groupColumn);
	if (!(zephir_array_isset_string_fetch(&groupColumn, params, SS("column") TSRMLS_CC))) {
		ZEPHIR_INIT_BNVAR(groupColumn);
		ZVAL_LONG(groupColumn, '*');
	}
	ZEPHIR_OBS_VAR(distinctColumn);
	if (zephir_array_isset_string_fetch(&distinctColumn, params, SS("distinct") TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_CONCAT_VS(_0, functionName, "(DISTINCT ");
		ZEPHIR_INIT_VAR(_1);
		concat_function(_1, _0, distinctColumn TSRMLS_CC);
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_VS(_2, _1, ") AS ");
		ZEPHIR_INIT_VAR(columns);
		concat_function(columns, _2, alias TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(columns);
		ZEPHIR_OBS_VAR(groupColumns);
		if (zephir_array_isset_string_fetch(&groupColumns, params, SS("group") TSRMLS_CC)) {
			ZEPHIR_INIT_LNVAR(_0);
			ZEPHIR_CONCAT_VS(_0, groupColumns, ", ");
			ZEPHIR_INIT_LNVAR(_1);
			concat_function(_1, _0, functionName TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_2);
			ZEPHIR_CONCAT_VS(_2, _1, "(");
			ZEPHIR_INIT_VAR(_3);
			concat_function(_3, _2, groupColumn TSRMLS_CC);
			ZEPHIR_INIT_VAR(_4);
			ZEPHIR_CONCAT_VS(_4, _3, ") AS ");
			concat_function(columns, _4, alias TSRMLS_CC);
		} else {
			ZEPHIR_INIT_LNVAR(_3);
			ZEPHIR_CONCAT_VS(_3, functionName, "(");
			ZEPHIR_INIT_LNVAR(_4);
			concat_function(_4, _3, groupColumn TSRMLS_CC);
			ZEPHIR_INIT_VAR(_5);
			ZEPHIR_CONCAT_VS(_5, _4, ") AS ");
			concat_function(columns, _5, alias TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_VAR(builder);
	object_init_ex(builder, phalcon_mvc_model_query_builder_ce);
	zephir_call_method_p1_noret(builder, "columns", columns);
	ZEPHIR_INIT_VAR(_6);
	zephir_call_func(_6, "get_called_class");
	zephir_call_method_p1_noret(builder, "from", _6);
	ZEPHIR_INIT_VAR(query);
	zephir_call_method(query, builder, "getquery");
	ZEPHIR_INIT_VAR(bindParams);
	ZVAL_NULL(bindParams);
	ZEPHIR_INIT_VAR(bindTypes);
	ZVAL_NULL(bindTypes);
	ZEPHIR_OBS_NVAR(bindParams);
	if (zephir_array_isset_string_fetch(&bindParams, params, SS("bind") TSRMLS_CC)) {
		ZEPHIR_OBS_NVAR(bindTypes);
	}
	ZEPHIR_INIT_VAR(resultset);
	zephir_call_method_p2(resultset, query, "execute", bindParams, bindTypes);
	ZEPHIR_OBS_VAR(cache);
	if (zephir_array_isset_string_fetch(&cache, params, SS("cache") TSRMLS_CC)) {
		zephir_call_method_p1_noret(query, "cache", cache);
	}
	if (zephir_array_isset_string(params, SS("group"))) {
		RETURN_CCTOR(resultset);
	}
	ZEPHIR_INIT_VAR(firstRow);
	zephir_call_method(firstRow, resultset, "getfirst");
	RETURN_MM_NULL();

}

/**
 * Allows to count how many records match the specified conditions
 *
 * <code>
 *
 * //How many robots are there?
 * $number = Robots::count();
 * echo "There are ", $number, "\n";
 *
 * //How many mechanical robots are there?
 * $number = Robots::count("type='mechanical'");
 * echo "There are ", $number, " mechanical robots\n";
 *
 * </code>
 *
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, count) {

	zval *parameters = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "COUNT", 1);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "rowcount", 1);
	zephir_call_self_p3(return_value, this_ptr, "_groupresult", _0, _1, parameters);
	RETURN_MM();

}

/**
 * Allows to calculate a summatory on a column that match the specified conditions
 *
 * <code>
 *
 * //How much are all robots?
 * $sum = Robots::sum(array('column' => 'price'));
 * echo "The total price of robots is ", $sum, "\n";
 *
 * //How much are mechanical robots?
 * $sum = Robots::sum(array("type='mechanical'", 'column' => 'price'));
 * echo "The total price of mechanical robots is  ", $sum, "\n";
 *
 * </code>
 *
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, sum) {

	zval *parameters = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "SUM", 1);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "sumatory", 1);
	zephir_call_self_p3(return_value, this_ptr, "_groupresult", _0, _1, parameters);
	RETURN_MM();

}

/**
 * Allows to get the maximum value of a column that match the specified conditions
 *
 * <code>
 *
 * //What is the maximum robot id?
 * $id = Robots::maximum(array('column' => 'id'));
 * echo "The maximum robot id is: ", $id, "\n";
 *
 * //What is the maximum id of mechanical robots?
 * $sum = Robots::maximum(array("type='mechanical'", 'column' => 'id'));
 * echo "The maximum robot id of mechanical robots is ", $id, "\n";
 *
 * </code>
 *
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, maximum) {

	zval *parameters = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "MAX", 1);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "maximum", 1);
	zephir_call_self_p3(return_value, this_ptr, "_groupresult", _0, _1, parameters);
	RETURN_MM();

}

/**
 * Allows to get the minimum value of a column that match the specified conditions
 *
 * <code>
 *
 * //What is the minimum robot id?
 * $id = Robots::minimum(array('column' => 'id'));
 * echo "The minimum robot id is: ", $id;
 *
 * //What is the minimum id of mechanical robots?
 * $sum = Robots::minimum(array("type='mechanical'", 'column' => 'id'));
 * echo "The minimum robot id of mechanical robots is ", $id;
 *
 * </code>
 *
 * @param array parameters
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, minimum) {

	zval *parameters = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "MIN", 1);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "minimum", 1);
	zephir_call_self_p3(return_value, this_ptr, "_groupresult", _0, _1, parameters);
	RETURN_MM();

}

/**
 * Allows to calculate the average value on a column matching the specified conditions
 *
 * <code>
 *
 * //What's the average price of robots?
 * $average = Robots::average(array('column' => 'price'));
 * echo "The average price is ", $average, "\n";
 *
 * //What's the average price of mechanical robots?
 * $average = Robots::average(array("type='mechanical'", 'column' => 'price'));
 * echo "The average price of mechanical robots is ", $average, "\n";
 *
 * </code>
 *
 * @param array parameters
 * @return double
 */
PHP_METHOD(Phalcon_Mvc_Model, average) {

	zval *parameters = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters);

	if (!parameters) {
		ZEPHIR_CPY_WRT(parameters, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "AVG", 1);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "average", 1);
	zephir_call_self_p3(return_value, this_ptr, "_groupresult", _0, _1, parameters);
	RETURN_MM();

}

/**
 * Fires an event, implicitly calls behaviors and listeners in the events manager are notified
 *
 * @param string eventName
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, fireEvent) {

	zval *eventName_param = NULL, *modelsManager = NULL, *_0;
	zval *eventName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &eventName_param);

		zephir_get_strval(eventName, eventName_param);


	if ((zephir_method_exists(this_ptr, eventName TSRMLS_CC)  == SUCCESS)) {
		zephir_call_method_zval_noret(this_ptr, eventName);
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _0);
	zephir_call_method_p2(return_value, modelsManager, "notifyevent", eventName, this_ptr);
	RETURN_MM();

}

/**
 * Fires an event, implicitly calls behaviors and listeners in the events manager are notified
 * This method stops if one of the callbacks/listeners returns boolean false
 *
 * @param string eventName
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, fireEventCancel) {

	zval *eventName_param = NULL, *modelsManager = NULL, *_0 = NULL, *_1;
	zval *eventName = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &eventName_param);

		zephir_get_strval(eventName, eventName_param);


	if ((zephir_method_exists(this_ptr, eventName TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_INIT_VAR(_0);
		zephir_call_method_zval(_0, this_ptr, eventName);
		if (ZEPHIR_IS_FALSE(_0)) {
			RETURN_MM_BOOL(0);
		}
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(modelsManager, _1);
	ZEPHIR_INIT_NVAR(_0);
	zephir_call_method_p2(_0, modelsManager, "notifyevent", eventName, this_ptr);
	if (ZEPHIR_IS_FALSE(_0)) {
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

/**
 * Cancel the current operation
 *
 */
PHP_METHOD(Phalcon_Mvc_Model, _cancelOperation) {

	zval *_0, *_1 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_operationMade"), PH_NOISY_CC);
	if (ZEPHIR_IS_LONG(_0, 3)) {
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "notDeleted", 1);
		zephir_call_method_p1_noret(this_ptr, "fireevent", _1);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "notSaved", 1);
		zephir_call_method_p1_noret(this_ptr, "fireevent", _1);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Appends a customized message on the validation process
 *
 * <code>
 * use \Phalcon\Mvc\Model\Message as Message;
 *
 * class Robots extends Phalcon\Mvc\Model
 * {
 *
 *   public function beforeSave()
 *   {
 *     if ($this->name == 'Peter') {
 *        $message = new Message("Sorry, but a robot cannot be named Peter");
 *        $this->appendMessage($message);
 *     }
 *   }
 * }
 * </code>
 *
 * @param Phalcon\Mvc\Model\MessageInterface message
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, appendMessage) {

	zval *message;

	zephir_fetch_params(0, 1, 0, &message);



	zephir_update_property_array_append(this_ptr, SL("_errorMessages"), message TSRMLS_CC);
	RETURN_THISW();

}

/**
 * Executes validators on every validation call
 *
 *<code>
 *use Phalcon\Mvc\Model\Validator\ExclusionIn as ExclusionIn;
 *
 *class Subscriptors extends Phalcon\Mvc\Model
 *{
 *
 *	public function validation()
 *  {
 * 		$this->validate(new ExclusionIn(array(
 *			'field' => 'status',
 *			'domain' => array('A', 'I')
 *		)));
 *		if ($this->validationHasFailed() == true) {
 *			return false;
 *		}
 *	}
 *
 *}
 *</code>
 *
 * @param object validator
 * @return Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, validate) {

	HashTable *_3;
	HashPosition _2;
	zval *validator, *message = NULL, *_0, *_1, **_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &validator);



	if ((Z_TYPE_P(validator) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Validator must be an Object");
		return;
	}
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method_p1(_0, validator, "validate", this_ptr);
	if (ZEPHIR_IS_FALSE(_0)) {
		ZEPHIR_INIT_VAR(_1);
		zephir_call_method(_1, validator, "getmessages");
		zephir_is_iterable(_1, &_3, &_2, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
			; zend_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(message, _4);
			zephir_update_property_array_append(this_ptr, SL("_errorMessages"), message TSRMLS_CC);
		}
	}
	RETURN_THIS();

}

/**
 * Check whether validation process has generated any messages
 *
 *<code>
 *use Phalcon\Mvc\Model\Validator\ExclusionIn as ExclusionIn;
 *
 *class Subscriptors extends Phalcon\Mvc\Model
 *{
 *
 *	public function validation()
 *  {
 * 		$this->validate(new ExclusionIn(array(
 *			'field' => 'status',
 *			'domain' => array('A', 'I')
 *		)));
 *		if ($this->validationHasFailed() == true) {
 *			return false;
 *		}
 *	}
 *
 *}
 *</code>
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, validationHasFailed) {

	zval *errorMessages;


	errorMessages = zephir_fetch_nproperty_this(this_ptr, SL("_errorMessages"), PH_NOISY_CC);
	if ((Z_TYPE_P(errorMessages) == IS_ARRAY)) {
		if (zephir_fast_count_int(errorMessages TSRMLS_CC)) {
			RETURN_BOOL(1);
		}
	}
	RETURN_BOOL(0);

}

/**
 * Returns all the validation messages
 *
 *<code>
 *	$robot = new Robots();
 *	$robot->type = 'mechanical';
 *	$robot->name = 'Astro Boy';
 *	$robot->year = 1952;
 *	if ($robot->save() == false) {
 *  	echo "Umh, We can't store robots right now ";
 *  	foreach ($robot->getMessages() as $message) {
 *			echo $message;
 *		}
 *	} else {
 *  	echo "Great, a new robot was saved successfully!";
 *	}
 * </code>
 *
 * @return Phalcon\Mvc\Model\MessageInterface[]
 */
PHP_METHOD(Phalcon_Mvc_Model, getMessages) {


	RETURN_MEMBER(this_ptr, "_errorMessages");

}

/**
 * Reads "belongs to" relations and check the virtual foreign keys when inserting or updating records
 * to verify that inserted/updated values are present in the related entity
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _checkForeignKeysRestrict) {

	zend_function *_4 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_21 = NULL, *_24 = NULL;
	HashTable *_2, *_11;
	HashPosition _1, _10;
	zend_bool error;
	zval *manager = NULL, *belongsTo, *foreignKey = NULL, *relation = NULL, *conditions = NULL, *position = NULL, *bindParams = NULL, *extraConditions = NULL, *message = NULL, *fields = NULL, *referencedFields = NULL, *field = NULL, *action = NULL, *referencedModel = NULL, *value = NULL, *_0, **_3, *_5 = NULL, **_12, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL, *_17 = NULL, *_18 = NULL, _19 = zval_used_for_init, *_20 = NULL, *_22 = NULL, *_23 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(manager, _0);
	ZEPHIR_INIT_VAR(belongsTo);
	zephir_call_method_p1(belongsTo, manager, "getbelongsto", this_ptr);
	if (zephir_fast_count_int(belongsTo TSRMLS_CC)) {
		error = 0;
		zephir_is_iterable(belongsTo, &_2, &_1, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
			; zend_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(relation, _3);
			ZEPHIR_INIT_NVAR(foreignKey);
			zephir_call_method_cache(foreignKey, relation, "getforeignkey", &_4);
			if (!ZEPHIR_IS_FALSE(foreignKey)) {
				ZEPHIR_INIT_NVAR(action);
				ZVAL_LONG(action, 1);
				if ((Z_TYPE_P(foreignKey) == IS_ARRAY)) {
					ZEPHIR_OBS_NVAR(action);
				}
				if (ZEPHIR_IS_LONG(action, 1)) {
					ZEPHIR_INIT_NVAR(_5);
					zephir_call_method_cache(_5, relation, "getreferencedmodel", &_6);
					ZEPHIR_INIT_NVAR(referencedModel);
					zephir_call_method_p1_cache(referencedModel, manager, "load", &_7, _5);
					ZEPHIR_INIT_NVAR(conditions);
					array_init(conditions);
					ZEPHIR_INIT_NVAR(bindParams);
					array_init(bindParams);
					ZEPHIR_INIT_NVAR(fields);
					zephir_call_method_cache(fields, relation, "getfields", &_8);
					ZEPHIR_INIT_NVAR(referencedFields);
					zephir_call_method_cache(referencedFields, relation, "getreferencedfields", &_9);
					if ((Z_TYPE_P(fields) == IS_ARRAY)) {
						zephir_is_iterable(fields, &_11, &_10, 0, 0);
						for (
							; zend_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
							; zend_hash_move_forward_ex(_11, &_10)
						) {
							ZEPHIR_GET_HMKEY(position, _11, _10);
							ZEPHIR_GET_HVALUE(field, _12);
							ZEPHIR_OBS_NVAR(value);
							ZEPHIR_OBS_NVAR(_13);
							zephir_array_fetch(&_13, referencedFields, position, PH_NOISY TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_14);
							ZEPHIR_CONCAT_SV(_14, "[", _13);
							ZEPHIR_INIT_LNVAR(_15);
							ZEPHIR_CONCAT_VS(_15, _14, "] = ?");
							ZEPHIR_INIT_LNVAR(_16);
							concat_function(_16, _15, position TSRMLS_CC);
							zephir_array_append(&conditions, _16, PH_SEPARATE);
							zephir_array_append(&bindParams, value, PH_SEPARATE);
						}
					} else {
						ZEPHIR_OBS_NVAR(value);
						ZEPHIR_INIT_LNVAR(_14);
						ZEPHIR_CONCAT_SV(_14, "[", referencedFields);
						ZEPHIR_INIT_LNVAR(_15);
						ZEPHIR_CONCAT_VS(_15, _14, "] = ?0");
						zephir_array_append(&conditions, _15, PH_SEPARATE);
						zephir_array_append(&bindParams, value, PH_SEPARATE);
					}
					ZEPHIR_OBS_NVAR(extraConditions);
					if (zephir_array_isset_string_fetch(&extraConditions, foreignKey, SS("conditions") TSRMLS_CC)) {
						zephir_array_append(&conditions, extraConditions, PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_17);
					ZEPHIR_INIT_NVAR(_18);
					array_init(_18);
					ZEPHIR_SINIT_NVAR(_19);
					ZVAL_STRING(&_19, " AND ", 0);
					ZEPHIR_INIT_NVAR(_20);
					zephir_call_func_p2(_20, "join", &_19, conditions);
					zephir_array_append(&_18, _20, 0);
					zephir_array_update_string(&_18, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
					zephir_call_method_p1_cache(_17, referencedModel, "count", &_21, _18);
					if (!(zephir_is_true(_17))) {
						ZEPHIR_OBS_NVAR(message);
						if (!(zephir_array_isset_string_fetch(&message, foreignKey, SS("message") TSRMLS_CC))) {
							ZEPHIR_INIT_NVAR(message);
							if ((Z_TYPE_P(fields) == IS_ARRAY)) {
								ZEPHIR_SINIT_NVAR(_19);
								ZVAL_STRING(&_19, ", ", 0);
								ZEPHIR_INIT_NVAR(_20);
								zephir_call_func_p2(_20, "join", &_19, fields);
								ZEPHIR_INIT_LNVAR(_16);
								ZEPHIR_CONCAT_SV(_16, "Value of fields '", _20);
								ZEPHIR_CONCAT_VS(message, _16, "' does not exist on referenced table");
							} else {
								ZEPHIR_INIT_LNVAR(_22);
								ZEPHIR_CONCAT_SV(_22, "Value of field '", fields);
								ZEPHIR_CONCAT_VS(message, _22, "' does not exist on referenced table");
							}
						}
						ZEPHIR_INIT_NVAR(_23);
						object_init_ex(_23, phalcon_mvc_model_message_ce);
						zephir_call_method_p1_cache_noret(this_ptr, "appendmessage", &_24, _23);
						error = 1;
						break;
					}
				}
			}
		}
		if ((error == 1)) {
			ZEPHIR_INIT_NVAR(_5);
			ZVAL_STRING(_5, "orm.events", 1);
			ZEPHIR_INIT_NVAR(_17);
			zephir_call_func_p1(_17, "globals_get", _5);
			if (zephir_is_true(_17)) {
				ZEPHIR_INIT_NVAR(_5);
				ZVAL_STRING(_5, "onValidationFails", 1);
				zephir_call_method_p1_noret(this_ptr, "fireevent", _5);
				zephir_call_method_noret(this_ptr, "_canceloperation");
			}
			RETURN_MM_BOOL(0);
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Reads both "hasMany" and "hasOne" relations and checks the virtual foreign keys (cascade) when deleting records
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _checkForeignKeysReverseCascade) {

	zend_function *_4 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_20 = NULL, *_21 = NULL;
	HashTable *_2, *_11;
	HashPosition _1, _10;
	zval *manager = NULL, *relations, *relation = NULL, *foreignKey = NULL, *resulset = NULL, *conditions = NULL, *bindParams = NULL, *referencedModel = NULL, *referencedFields = NULL, *action = NULL, *fields = NULL, *field = NULL, *position = NULL, *value = NULL, *extraConditions = NULL, *_0, **_3, *_5 = NULL, **_12, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL, *_17 = NULL, _18 = zval_used_for_init, *_19 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_CPY_WRT(manager, _0);
	ZEPHIR_INIT_VAR(relations);
	zephir_call_method_p1(relations, manager, "gethasoneandhasmany", this_ptr);
	if (zephir_fast_count_int(relations TSRMLS_CC)) {
		zephir_is_iterable(relations, &_2, &_1, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
			; zend_hash_move_forward_ex(_2, &_1)
		) {
			ZEPHIR_GET_HVALUE(relation, _3);
			ZEPHIR_INIT_NVAR(foreignKey);
			zephir_call_method_cache(foreignKey, relation, "getforeignkey", &_4);
			if (!ZEPHIR_IS_FALSE(foreignKey)) {
				ZEPHIR_INIT_NVAR(action);
				ZVAL_LONG(action, 0);
				if ((Z_TYPE_P(foreignKey) == IS_ARRAY)) {
					ZEPHIR_OBS_NVAR(action);
				}
				if (ZEPHIR_IS_LONG(action, 2)) {
					ZEPHIR_INIT_NVAR(_5);
					zephir_call_method_cache(_5, relation, "getreferencedmodel", &_6);
					ZEPHIR_INIT_NVAR(referencedModel);
					zephir_call_method_p1_cache(referencedModel, manager, "load", &_7, _5);
					ZEPHIR_INIT_NVAR(fields);
					zephir_call_method_cache(fields, relation, "getfields", &_8);
					ZEPHIR_INIT_NVAR(referencedFields);
					zephir_call_method_cache(referencedFields, relation, "getreferencedfields", &_9);
					ZEPHIR_INIT_NVAR(conditions);
					array_init(conditions);
					ZEPHIR_INIT_NVAR(bindParams);
					array_init(bindParams);
					if ((Z_TYPE_P(fields) == IS_ARRAY)) {
						zephir_is_iterable(fields, &_11, &_10, 0, 0);
						for (
							; zend_hash_get_current_data_ex(_11, (void**) &_12, &_10) == SUCCESS
							; zend_hash_move_forward_ex(_11, &_10)
						) {
							ZEPHIR_GET_HMKEY(position, _11, _10);
							ZEPHIR_GET_HVALUE(field, _12);
							ZEPHIR_OBS_NVAR(value);
							ZEPHIR_OBS_NVAR(_13);
							zephir_array_fetch(&_13, referencedFields, position, PH_NOISY TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_14);
							ZEPHIR_CONCAT_SV(_14, "[", _13);
							ZEPHIR_INIT_LNVAR(_15);
							ZEPHIR_CONCAT_VS(_15, _14, "] = ?");
							ZEPHIR_INIT_LNVAR(_16);
							concat_function(_16, _15, position TSRMLS_CC);
							zephir_array_append(&conditions, _16, PH_SEPARATE);
							zephir_array_append(&bindParams, value, PH_SEPARATE);
						}
					} else {
						ZEPHIR_OBS_NVAR(value);
						ZEPHIR_INIT_LNVAR(_14);
						ZEPHIR_CONCAT_SV(_14, "[", referencedFields);
						ZEPHIR_INIT_LNVAR(_15);
						ZEPHIR_CONCAT_VS(_15, _14, "] = ?0");
						zephir_array_append(&conditions, _15, PH_SEPARATE);
						zephir_array_append(&bindParams, value, PH_SEPARATE);
					}
					ZEPHIR_OBS_NVAR(extraConditions);
					if (zephir_array_isset_string_fetch(&extraConditions, foreignKey, SS("conditions") TSRMLS_CC)) {
						zephir_array_append(&conditions, extraConditions, PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_17);
					array_init(_17);
					ZEPHIR_SINIT_NVAR(_18);
					ZVAL_STRING(&_18, " AND ", 0);
					ZEPHIR_INIT_NVAR(_19);
					zephir_call_func_p2(_19, "join", &_18, conditions);
					zephir_array_append(&_17, _19, 0);
					zephir_array_update_string(&_17, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
					ZEPHIR_INIT_NVAR(resulset);
					zephir_call_method_p1_cache(resulset, referencedModel, "find", &_20, _17);
					ZEPHIR_INIT_NVAR(_19);
					zephir_call_method_cache(_19, resulset, "delete", &_21);
					if (ZEPHIR_IS_FALSE(_19)) {
						RETURN_MM_BOOL(0);
					}
				}
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Reads both "hasMany" and "hasOne" relations and checks the virtual foreign keys (restrict) when deleting records
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _checkForeignKeysReverseRestrict) {

	zend_function *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_19 = NULL, *_20 = NULL;
	HashTable *_1, *_9;
	HashPosition _0, _8;
	zend_bool error;
	zval *manager, *relations, *foreignKey = NULL, *action = NULL, *relation = NULL, *relationClass = NULL, *referencedModel = NULL, *fields = NULL, *referencedFields = NULL, *conditions = NULL, *bindParams = NULL, *position = NULL, *field = NULL, *value = NULL, *extraConditions = NULL, *message = NULL, **_2, **_10, *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL, *_15 = NULL, *_16 = NULL, _17 = zval_used_for_init, *_18 = NULL;

	ZEPHIR_MM_GROW();

	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(relations);
	zephir_call_method_p1(relations, manager, "gethasoneandhasmany", this_ptr);
	if (zephir_fast_count_int(relations TSRMLS_CC)) {
		error = 0;
		zephir_is_iterable(relations, &_1, &_0, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
			; zend_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(relation, _2);
			ZEPHIR_INIT_NVAR(foreignKey);
			zephir_call_method_cache(foreignKey, relation, "getforeignkey", &_3);
			if (!ZEPHIR_IS_FALSE(foreignKey)) {
				ZEPHIR_INIT_NVAR(action);
				ZVAL_LONG(action, 1);
				if ((Z_TYPE_P(foreignKey) == IS_ARRAY)) {
					ZEPHIR_OBS_NVAR(action);
				}
				if (ZEPHIR_IS_LONG(action, 1)) {
					ZEPHIR_INIT_NVAR(relationClass);
					zephir_call_method_cache(relationClass, relation, "getreferencedmodel", &_4);
					ZEPHIR_INIT_NVAR(referencedModel);
					zephir_call_method_p1_cache(referencedModel, manager, "load", &_5, relationClass);
					ZEPHIR_INIT_NVAR(fields);
					zephir_call_method_cache(fields, relation, "getfields", &_6);
					ZEPHIR_INIT_NVAR(referencedFields);
					zephir_call_method_cache(referencedFields, relation, "getreferencedfields", &_7);
					ZEPHIR_INIT_NVAR(conditions);
					array_init(conditions);
					ZEPHIR_INIT_NVAR(bindParams);
					array_init(bindParams);
					if ((Z_TYPE_P(fields) == IS_ARRAY)) {
						zephir_is_iterable(fields, &_9, &_8, 0, 0);
						for (
							; zend_hash_get_current_data_ex(_9, (void**) &_10, &_8) == SUCCESS
							; zend_hash_move_forward_ex(_9, &_8)
						) {
							ZEPHIR_GET_HMKEY(position, _9, _8);
							ZEPHIR_GET_HVALUE(field, _10);
							ZEPHIR_OBS_NVAR(value);
							ZEPHIR_OBS_NVAR(_11);
							zephir_array_fetch(&_11, referencedFields, position, PH_NOISY TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_12);
							ZEPHIR_CONCAT_SV(_12, "[", _11);
							ZEPHIR_INIT_LNVAR(_13);
							ZEPHIR_CONCAT_VS(_13, _12, "] = ?");
							ZEPHIR_INIT_LNVAR(_14);
							concat_function(_14, _13, position TSRMLS_CC);
							zephir_array_append(&conditions, _14, PH_SEPARATE);
							zephir_array_append(&bindParams, value, PH_SEPARATE);
						}
					} else {
						ZEPHIR_OBS_NVAR(value);
						ZEPHIR_INIT_LNVAR(_12);
						ZEPHIR_CONCAT_SV(_12, "[", referencedFields);
						ZEPHIR_INIT_LNVAR(_13);
						ZEPHIR_CONCAT_VS(_13, _12, "] = ?0");
						zephir_array_append(&conditions, _13, PH_SEPARATE);
						zephir_array_append(&bindParams, value, PH_SEPARATE);
					}
					ZEPHIR_OBS_NVAR(extraConditions);
					if (zephir_array_isset_string_fetch(&extraConditions, foreignKey, SS("conditions") TSRMLS_CC)) {
						zephir_array_append(&conditions, extraConditions, PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_15);
					ZEPHIR_INIT_NVAR(_16);
					array_init(_16);
					ZEPHIR_SINIT_NVAR(_17);
					ZVAL_STRING(&_17, " AND ", 0);
					ZEPHIR_INIT_NVAR(_18);
					zephir_call_func_p2(_18, "join", &_17, conditions);
					zephir_array_append(&_16, _18, 0);
					zephir_array_update_string(&_16, SL("bind"), &bindParams, PH_COPY | PH_SEPARATE);
					zephir_call_method_p1_cache(_15, referencedModel, "count", &_19, _16);
					if (zephir_is_true(_15)) {
						ZEPHIR_OBS_NVAR(message);
						if (!(zephir_array_isset_string_fetch(&message, foreignKey, SS("message") TSRMLS_CC))) {
							ZEPHIR_INIT_NVAR(message);
							ZEPHIR_CONCAT_SV(message, "Record is referenced by model ", relationClass);
						}
						ZEPHIR_INIT_NVAR(_18);
						object_init_ex(_18, phalcon_mvc_model_message_ce);
						zephir_call_method_p1_cache_noret(this_ptr, "appendmessage", &_20, _18);
						error = 1;
						break;
					}
				}
			}
		}
		if ((error == 1)) {
			ZEPHIR_INIT_NVAR(_15);
			ZVAL_STRING(_15, "orm.events", 1);
			ZEPHIR_INIT_NVAR(_16);
			zephir_call_func_p1(_16, "globals_get", _15);
			if (zephir_is_true(_16)) {
				ZEPHIR_INIT_NVAR(_15);
				ZVAL_STRING(_15, "onValidationFails", 1);
				zephir_call_method_p1_noret(this_ptr, "fireevent", _15);
				zephir_call_method_noret(this_ptr, "_canceloperation");
			}
			RETURN_MM_BOOL(0);
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Executes internal hooks before save a record
 *
 * @param Phalcon\Mvc\Model\MetadataInterface metaData
 * @param boolean exists
 * @param string identityField
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _preSave) {

	zend_function *_10 = NULL;
	HashTable *_6;
	HashPosition _5;
	zend_bool exists, error, isNull;
	zval *metaData, *exists_param = NULL, *identityField, *notNull, *columnMap, *dataTypeNumeric, *automaticAttributes, *field = NULL, *attributeField = NULL, *value = NULL, *_0, *_1, *_2 = NULL, *_3 = NULL, *_4 = NULL, **_7, *_8 = NULL, *_9 = NULL, *_11 = NULL, *_12, *_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &metaData, &exists_param, &identityField);

		exists = zephir_get_boolval(exists_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "orm.events", 1);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_func_p1(_1, "globals_get", _0);
	if (zephir_is_true(_1)) {
		ZEPHIR_INIT_BNVAR(_0);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "beforeValidation", 1);
		zephir_call_method_p1(_0, this_ptr, "fireeventcancel", _2);
		if (ZEPHIR_IS_FALSE(_0)) {
			RETURN_MM_BOOL(0);
		}
		if (exists) {
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_INIT_VAR(_3);
			ZVAL_STRING(_3, "beforeValidationOnCreate", 1);
			zephir_call_method_p1(_2, this_ptr, "fireeventcancel", _3);
			if (ZEPHIR_IS_FALSE(_2)) {
				RETURN_MM_BOOL(0);
			}
		} else {
			ZEPHIR_INIT_NVAR(_3);
			ZEPHIR_INIT_VAR(_4);
			ZVAL_STRING(_4, "beforeValidationOnUpdate", 1);
			zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
			if (ZEPHIR_IS_FALSE(_3)) {
				RETURN_MM_BOOL(0);
			}
		}
	}
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "orm.virtual_foreign_keys", 1);
	ZEPHIR_INIT_NVAR(_3);
	zephir_call_func_p1(_3, "globals_get", _2);
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_NVAR(_2);
		zephir_call_method(_2, this_ptr, "_checkforeignkeysrestrict");
		if (ZEPHIR_IS_FALSE(_2)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "orm.not_null_validations", 1);
	ZEPHIR_INIT_NVAR(_3);
	zephir_call_func_p1(_3, "globals_get", _2);
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_VAR(notNull);
		zephir_call_method_p1(notNull, metaData, "getnotnullattributes", this_ptr);
		if ((Z_TYPE_P(notNull) == IS_ARRAY)) {
			ZEPHIR_INIT_VAR(dataTypeNumeric);
			zephir_call_method_p1(dataTypeNumeric, metaData, "getdatatypesnumeric", this_ptr);
			ZEPHIR_INIT_VAR(columnMap);
			ZEPHIR_INIT_NVAR(_2);
			ZVAL_STRING(_2, "orm.column_renaming", 1);
			ZEPHIR_INIT_NVAR(_4);
			zephir_call_func_p1(_4, "globals_get", _2);
			if (zephir_is_true(_4)) {
				zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
			} else {
				ZVAL_NULL(columnMap);
			}
			ZEPHIR_INIT_VAR(automaticAttributes);
			if (exists) {
				zephir_call_method_p1(automaticAttributes, metaData, "getautomaticupdateattributes", this_ptr);
			} else {
				zephir_call_method_p1(automaticAttributes, metaData, "getautomaticcreateattributes", this_ptr);
			}
			error = 0;
			zephir_is_iterable(notNull, &_6, &_5, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
				; zend_hash_move_forward_ex(_6, &_5)
			) {
				ZEPHIR_GET_HVALUE(field, _7);
				if (!(zephir_array_isset(automaticAttributes, field))) {
					isNull = 0;
					if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
						ZEPHIR_OBS_NVAR(attributeField);
						if (!(zephir_array_isset_fetch(&attributeField, columnMap, field TSRMLS_CC))) {
							ZEPHIR_INIT_NVAR(_2);
							object_init_ex(_2, phalcon_mvc_model_exception_ce);
							ZEPHIR_INIT_LNVAR(_8);
							ZEPHIR_CONCAT_SV(_8, "Column '", field);
							ZEPHIR_INIT_LNVAR(_9);
							ZEPHIR_CONCAT_VS(_9, _8, "' isn't part of the column map");
							zephir_call_method_p1_cache_noret(_2, "__construct", &_10, _9);
							zephir_throw_exception(_2 TSRMLS_CC);
							ZEPHIR_MM_RESTORE();
							return;
						}
					} else {
						ZEPHIR_CPY_WRT(attributeField, field);
					}
					ZEPHIR_OBS_NVAR(value);
					if (0) {
						if ((Z_TYPE_P(value) != IS_OBJECT)) {
							if (!(zephir_array_isset(dataTypeNumeric, field))) {
								if (0) {
									isNull = 1;
								}
							} else {
								if (!(zephir_is_numeric(value))) {
									isNull = 1;
								}
							}
						}
					} else {
						isNull = 1;
					}
					if ((isNull == 1)) {
						if (!(exists)) {
							if (ZEPHIR_IS_EQUAL(field, identityField)) {
								continue;
							}
						}
						ZEPHIR_INIT_NVAR(_2);
						object_init_ex(_2, phalcon_mvc_model_message_ce);
						zephir_update_property_array_append(this_ptr, SL("_errorMessages"), _2 TSRMLS_CC);
						error = 1;
					}
				}
			}
			if ((error == 1)) {
				ZEPHIR_INIT_VAR(_11);
				ZVAL_STRING(_11, "orm.events", 1);
				ZEPHIR_INIT_VAR(_12);
				zephir_call_func_p1(_12, "globals_get", _11);
				if (zephir_is_true(_12)) {
					ZEPHIR_INIT_NVAR(_11);
					ZVAL_STRING(_11, "onValidationFails", 1);
					zephir_call_method_p1_noret(this_ptr, "fireevent", _11);
					zephir_call_method_noret(this_ptr, "_canceloperation");
				}
				RETURN_MM_BOOL(0);
			}
		}
	}
	ZEPHIR_INIT_NVAR(_2);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_STRING(_3, "validation", 1);
	zephir_call_method_p1(_2, this_ptr, "fireeventcancel", _3);
	if (ZEPHIR_IS_FALSE(_2)) {
		ZEPHIR_INIT_NVAR(_3);
		ZVAL_STRING(_3, "orm.events", 1);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_func_p1(_4, "globals_get", _3);
		if (zephir_is_true(_4)) {
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "onValidationFails", 1);
			zephir_call_method_p1_noret(this_ptr, "fireevent", _3);
		}
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_STRING(_2, "orm.events", 1);
	ZEPHIR_INIT_NVAR(_3);
	zephir_call_func_p1(_3, "globals_get", _2);
	if (zephir_is_true(_3)) {
		if (!(exists)) {
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "afterValidationOnCreate", 1);
			zephir_call_method_p1(_2, this_ptr, "fireeventcancel", _4);
			if (ZEPHIR_IS_FALSE(_2)) {
				RETURN_MM_BOOL(0);
			}
		} else {
			ZEPHIR_INIT_NVAR(_3);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "afterValidationOnUpdate", 1);
			zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
			if (ZEPHIR_IS_FALSE(_3)) {
				RETURN_MM_BOOL(0);
			}
		}
		ZEPHIR_INIT_NVAR(_3);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "afterValidation", 1);
		zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
		if (ZEPHIR_IS_FALSE(_3)) {
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_NVAR(_3);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "beforeSave", 1);
		zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
		if (ZEPHIR_IS_FALSE(_3)) {
			RETURN_MM_BOOL(0);
		}
		zephir_update_property_this(this_ptr, SL("_skipped"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		if (exists) {
			ZEPHIR_INIT_NVAR(_3);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "beforeUpdate", 1);
			zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
			if (ZEPHIR_IS_FALSE(_3)) {
				RETURN_MM_BOOL(0);
			}
		} else {
			ZEPHIR_INIT_NVAR(_3);
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "beforeCreate", 1);
			zephir_call_method_p1(_3, this_ptr, "fireeventcancel", _4);
			if (ZEPHIR_IS_FALSE(_3)) {
				RETURN_MM_BOOL(0);
			}
		}
		_13 = zephir_fetch_nproperty_this(this_ptr, SL("_skipped"), PH_NOISY_CC);
		if (ZEPHIR_IS_TRUE(_13)) {
			RETURN_MM_BOOL(1);
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Executes internal events after save a record
 *
 * @param boolean success
 * @param boolean exists
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _postSave) {

	zval *success_param = NULL, *exists_param = NULL, *_0 = NULL;
	zend_bool success, exists;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &success_param, &exists_param);

		success = zephir_get_boolval(success_param);
		exists = zephir_get_boolval(exists_param);


	if ((success == 1)) {
		if (exists) {
			ZEPHIR_INIT_VAR(_0);
			ZVAL_STRING(_0, "afterUpdate", 1);
			zephir_call_method_p1_noret(this_ptr, "fireevent", _0);
		} else {
			ZEPHIR_INIT_NVAR(_0);
			ZVAL_STRING(_0, "afterCreate", 1);
			zephir_call_method_p1_noret(this_ptr, "fireevent", _0);
		}
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "afterSave", 1);
		zephir_call_method_p1_noret(this_ptr, "fireevent", _0);
		RETURN_MM_BOOL(success);
	}
	ZEPHIR_INIT_NVAR(_0);
	ZVAL_STRING(_0, "notSave", 1);
	zephir_call_method_p1_noret(this_ptr, "fireevent", _0);
	zephir_call_method_noret(this_ptr, "_canceloperation");
	RETURN_MM_BOOL(0);

}

/**
 * Sends a pre-build INSERT SQL statement to the relational database system
 *
 * @param Phalcon\Mvc\Model\MetadataInterface metaData
 * @param Phalcon\Db\AdapterInterface connection
 * @param string|array table
 * @param boolean|string identityField
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _doLowInsert) {

	zend_function *_7 = NULL, *_8 = NULL;
	HashTable *_3;
	HashPosition _2;
	zend_bool useExplicitIdentity;
	zval *metaData, *connection, *table, *identityField, *bindSkip, *fields, *values, *bindTypes, *attributes, *bindDataTypes, *automaticAttributes, *field = NULL, *columnMap, *value = NULL, *attributeField = NULL, *success, *bindType = NULL, *defaultValue, *sequenceName = NULL, *_0 = NULL, *_1, **_4, *_5 = NULL, *_6 = NULL, *_9 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &metaData, &connection, &table, &identityField);



	ZEPHIR_INIT_VAR(bindSkip);
	ZVAL_LONG(bindSkip, 1024);
	ZEPHIR_INIT_VAR(fields);
	array_init(fields);
	ZEPHIR_INIT_VAR(values);
	array_init(values);
	ZEPHIR_INIT_VAR(bindTypes);
	array_init(bindTypes);
	ZEPHIR_INIT_VAR(attributes);
	zephir_call_method_p1(attributes, metaData, "getattributes", this_ptr);
	ZEPHIR_INIT_VAR(bindDataTypes);
	zephir_call_method_p1(bindDataTypes, metaData, "getbindtypes", this_ptr);
	ZEPHIR_INIT_VAR(automaticAttributes);
	zephir_call_method_p1(automaticAttributes, metaData, "getautomaticcreateattributes", this_ptr);
	ZEPHIR_INIT_VAR(columnMap);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "orm.column_renaming", 1);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_func_p1(_1, "globals_get", _0);
	if (zephir_is_true(_1)) {
		zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
	} else {
		ZVAL_NULL(columnMap);
	}
	zephir_is_iterable(attributes, &_3, &_2, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		; zend_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(field, _4);
		if (!(zephir_array_isset(automaticAttributes, field))) {
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, field TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_0);
					object_init_ex(_0, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_5);
					ZEPHIR_CONCAT_SV(_5, "Column '", field);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_VS(_6, _5, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_0, "__construct", &_7, _6);
					zephir_throw_exception(_0 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, field);
			}
			if (!ZEPHIR_IS_EQUAL(field, identityField)) {
				zephir_array_append(&fields, field, PH_SEPARATE);
				ZEPHIR_OBS_NVAR(value);
				if (0) {
					ZEPHIR_OBS_NVAR(bindType);
					if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, field TSRMLS_CC))) {
						ZEPHIR_INIT_NVAR(_0);
						object_init_ex(_0, phalcon_mvc_model_exception_ce);
						ZEPHIR_INIT_LNVAR(_5);
						ZEPHIR_CONCAT_SV(_5, "Column '", field);
						ZEPHIR_INIT_LNVAR(_6);
						ZEPHIR_CONCAT_VS(_6, _5, "' have not defined a bind data type");
						zephir_call_method_p1_cache_noret(_0, "__construct", &_8, _6);
						zephir_throw_exception(_0 TSRMLS_CC);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_array_append(&values, value, PH_SEPARATE);
					zephir_array_append(&bindTypes, bindType, PH_SEPARATE);
				} else {
					zephir_array_append(&values, ZEPHIR_GLOBAL(global_null), PH_SEPARATE);
					zephir_array_append(&bindTypes, bindSkip, PH_SEPARATE);
				}
			}
		}
	}
	if (!ZEPHIR_IS_FALSE(identityField)) {
		ZEPHIR_INIT_VAR(defaultValue);
		zephir_call_method(defaultValue, connection, "getdefaultidvalue");
		ZEPHIR_INIT_BNVAR(_0);
		zephir_call_method(_0, connection, "useexplicitidvalue");
		useExplicitIdentity = (zephir_get_boolval(_0)) ? 1 : 0;
		if (useExplicitIdentity) {
			zephir_array_append(&fields, identityField, PH_SEPARATE);
		}
		if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
			ZEPHIR_OBS_NVAR(attributeField);
			if (!(zephir_array_isset_fetch(&attributeField, columnMap, identityField TSRMLS_CC))) {
				ZEPHIR_INIT_VAR(_9);
				object_init_ex(_9, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_SV(_5, "Identity column '", identityField);
				ZEPHIR_INIT_LNVAR(_6);
				ZEPHIR_CONCAT_VS(_6, _5, "' isn't part of the column map");
				zephir_call_method_p1_noret(_9, "__construct", _6);
				zephir_throw_exception(_9 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(attributeField, identityField);
		}
		ZEPHIR_OBS_NVAR(value);
		if (0) {
			if (0) {
				if (useExplicitIdentity) {
					zephir_array_append(&values, defaultValue, PH_SEPARATE);
					zephir_array_append(&bindTypes, bindSkip, PH_SEPARATE);
				}
			} else {
				if (!(useExplicitIdentity)) {
					zephir_array_append(&fields, identityField, PH_SEPARATE);
				}
				ZEPHIR_OBS_NVAR(bindType);
				if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, identityField TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_9);
					object_init_ex(_9, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_5);
					ZEPHIR_CONCAT_SV(_5, "Identity column '", identityField);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_VS(_6, _5, "' isn\'t part of the table columns");
					zephir_call_method_p1_noret(_9, "__construct", _6);
					zephir_throw_exception(_9 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_array_append(&values, value, PH_SEPARATE);
				zephir_array_append(&bindTypes, bindType, PH_SEPARATE);
			}
		} else {
			if (useExplicitIdentity) {
				zephir_array_append(&values, defaultValue, PH_SEPARATE);
				zephir_array_append(&bindTypes, bindSkip, PH_SEPARATE);
			}
		}
	}
	ZEPHIR_INIT_VAR(success);
	zephir_call_method_p4(success, connection, "insert", table, values, fields, bindTypes);
	if (zephir_is_true(success) && !ZEPHIR_IS_FALSE(identityField)) {
		ZEPHIR_INIT_VAR(sequenceName);
		ZVAL_NULL(sequenceName);
		ZEPHIR_INIT_NVAR(_9);
		zephir_call_method(_9, connection, "supportsequences");
		if (ZEPHIR_IS_TRUE(_9)) {
			ZEPHIR_INIT_NVAR(sequenceName);
			if ((zephir_method_exists_str(this_ptr, SS("getsequencename") TSRMLS_CC) == SUCCESS)) {
				zephir_call_method(sequenceName, this_ptr, "getsequencename");
			} else {
				ZEPHIR_INIT_NVAR(_9);
				zephir_call_method(_9, this_ptr, "getsource");
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_VS(_5, _9, "_");
				ZEPHIR_INIT_LNVAR(_6);
				concat_function(_6, _5, identityField TSRMLS_CC);
				ZEPHIR_CONCAT_VS(sequenceName, _6, "_seq");
			}
		}
		ZEPHIR_INIT_NVAR(_9);
		zephir_call_method_p1(_9, connection, "lastinsertid", sequenceName);
		zephir_update_property_zval_zval(this_ptr, attributeField, _9 TSRMLS_CC);
		zephir_update_property_this(this_ptr, SL("_uniqueParams"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	}
	RETURN_CCTOR(success);

}

/**
 * Sends a pre-build UPDATE SQL statement to the relational database system
 *
 * @param Phalcon\Mvc\Model\MetaDataInterface metaData
 * @param Phalcon\Db\AdapterInterface connection
 * @param string|array table
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _doLowUpdate) {

	zend_function *_8 = NULL, *_9 = NULL, *_14 = NULL;
	HashTable *_4, *_12;
	HashPosition _3, _11;
	zend_bool useDynamicUpdate, changed;
	zval *metaData, *connection, *table, *bindSkip, *fields, *values, *bindTypes, *manager, *bindDataTypes, *field = NULL, *automaticAttributes, *snapshotValue = NULL, *uniqueKey, *uniqueParams, *uniqueTypes, *snapshot, *nonPrimary, *columnMap, *attributeField = NULL, *value = NULL, *primaryKeys, *_0, *_1 = NULL, *_2, **_5, *_6 = NULL, *_7 = NULL, *_10, **_13;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &metaData, &connection, &table);



	ZEPHIR_INIT_VAR(bindSkip);
	ZVAL_LONG(bindSkip, 1024);
	ZEPHIR_INIT_VAR(fields);
	array_init(fields);
	ZEPHIR_INIT_VAR(values);
	array_init(values);
	ZEPHIR_INIT_VAR(bindTypes);
	array_init(bindTypes);
	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method_p1(_0, manager, "isusingdynamicupdate", this_ptr);
	useDynamicUpdate = (zephir_get_boolval(_0)) ? 1 : 0;
	if (useDynamicUpdate) {
		snapshot = zephir_fetch_nproperty_this(this_ptr, SL("_snapshot"), PH_NOISY_CC);
		if ((Z_TYPE_P(snapshot) != IS_ARRAY)) {
			useDynamicUpdate = 0;
		}
	}
	ZEPHIR_INIT_VAR(bindDataTypes);
	zephir_call_method_p1(bindDataTypes, metaData, "getbindtypes", this_ptr);
	ZEPHIR_INIT_VAR(nonPrimary);
	zephir_call_method_p1(nonPrimary, metaData, "getnonprimarykeyattributes", this_ptr);
	ZEPHIR_INIT_VAR(automaticAttributes);
	zephir_call_method_p1(automaticAttributes, metaData, "getautomaticupdateattributes", this_ptr);
	ZEPHIR_INIT_VAR(columnMap);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "orm.column_renaming", 1);
	ZEPHIR_INIT_VAR(_2);
	zephir_call_func_p1(_2, "globals_get", _1);
	if (zephir_is_true(_2)) {
		zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
	} else {
		ZVAL_NULL(columnMap);
	}
	zephir_is_iterable(nonPrimary, &_4, &_3, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
		; zend_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HVALUE(field, _5);
		if (!(zephir_array_isset(automaticAttributes, field))) {
			if (!(zephir_array_isset(bindDataTypes, field))) {
				ZEPHIR_INIT_NVAR(_1);
				object_init_ex(_1, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_6);
				ZEPHIR_CONCAT_SV(_6, "Column '", field);
				ZEPHIR_INIT_LNVAR(_7);
				ZEPHIR_CONCAT_VS(_7, _6, "' have not defined a bind data type");
				zephir_call_method_p1_cache_noret(_1, "__construct", &_8, _7);
				zephir_throw_exception(_1 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, field TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_1);
					object_init_ex(_1, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_SV(_6, "Column '", field);
					ZEPHIR_INIT_LNVAR(_7);
					ZEPHIR_CONCAT_VS(_7, _6, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_1, "__construct", &_9, _7);
					zephir_throw_exception(_1 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, field);
			}
			ZEPHIR_OBS_NVAR(value);
			if (0) {
				if (!(useDynamicUpdate)) {
					zephir_array_append(&fields, field, PH_SEPARATE);
					zephir_array_append(&values, value, PH_SEPARATE);
					zephir_array_fetch(&_10, bindDataTypes, field, PH_NOISY | PH_READONLY TSRMLS_CC);
					zephir_array_append(&bindTypes, _10, PH_SEPARATE);
				} else {
					ZEPHIR_OBS_NVAR(snapshotValue);
					if (!(zephir_array_isset_fetch(&snapshotValue, snapshot, attributeField TSRMLS_CC))) {
						changed = 1;
					} else {
						changed = !ZEPHIR_IS_EQUAL(value, snapshotValue);
					}
					if (changed) {
						zephir_array_append(&fields, field, PH_SEPARATE);
						zephir_array_append(&values, value, PH_SEPARATE);
						zephir_array_fetch(&_10, bindDataTypes, field, PH_NOISY | PH_READONLY TSRMLS_CC);
						zephir_array_append(&bindTypes, _10, PH_SEPARATE);
					}
				}
			} else {
				zephir_array_append(&fields, field, PH_SEPARATE);
				zephir_array_append(&values, ZEPHIR_GLOBAL(global_null), PH_SEPARATE);
				zephir_array_append(&bindTypes, bindSkip, PH_SEPARATE);
			}
		}
	}
	if (!(zephir_fast_count_int(fields TSRMLS_CC))) {
		RETURN_MM_BOOL(1);
	}
	uniqueKey = zephir_fetch_nproperty_this(this_ptr, SL("_uniqueKey"), PH_NOISY_CC);
	ZEPHIR_OBS_VAR(uniqueParams);
	zephir_read_property_this(&uniqueParams, this_ptr, SL("_uniqueParams"), PH_NOISY_CC);
	uniqueTypes = zephir_fetch_nproperty_this(this_ptr, SL("_uniqueTypes"), PH_NOISY_CC);
	if ((Z_TYPE_P(uniqueParams) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(primaryKeys);
		zephir_call_method_p1(primaryKeys, metaData, "getprimarykeyattributes", this_ptr);
		if (!(zephir_fast_count_int(primaryKeys TSRMLS_CC))) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "A primary key must be defined in the model in order to perform the operation");
			return;
		}
		ZEPHIR_INIT_BNVAR(uniqueParams);
		array_init(uniqueParams);
		zephir_is_iterable(primaryKeys, &_12, &_11, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_12, (void**) &_13, &_11) == SUCCESS
			; zend_hash_move_forward_ex(_12, &_11)
		) {
			ZEPHIR_GET_HVALUE(field, _13);
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, field TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_1);
					object_init_ex(_1, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_SV(_6, "Column '", field);
					ZEPHIR_INIT_LNVAR(_7);
					ZEPHIR_CONCAT_VS(_7, _6, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_1, "__construct", &_14, _7);
					zephir_throw_exception(_1 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, field);
			}
			ZEPHIR_OBS_NVAR(value);
			if (0) {
				zephir_array_append(&uniqueParams, value, PH_SEPARATE);
			} else {
				zephir_array_append(&uniqueParams, ZEPHIR_GLOBAL(global_null), PH_SEPARATE);
			}
		}
	}
	ZEPHIR_INIT_BNVAR(_1);
	array_init(_1);
	zephir_array_update_string(&_1, SL("conditions"), &uniqueKey, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("bind"), &uniqueParams, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("bindTypes"), &uniqueTypes, PH_COPY | PH_SEPARATE);
	zephir_call_method_p5(return_value, connection, "update", table, fields, values, _1, bindTypes);
	RETURN_MM();

}

/**
 * Saves related records that must be stored prior to save the master record
 *
 * @param Phalcon\Db\AdapterInterface connection
 * @param Phalcon\Mvc\ModelInterface[] related
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _preSaveRelatedRecords) {

	zend_function *_3 = NULL, *_4 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_11 = NULL, *_13 = NULL, *_17 = NULL, *_18 = NULL, *_19 = NULL, *_20 = NULL;
	HashTable *_1, *_15;
	HashPosition _0, _14;
	zend_bool nesting;
	zval *connection, *related, *className, *manager, *type = NULL, *relation = NULL, *columns = NULL, *referencedFields = NULL, *referencedModel = NULL, *message = NULL, *name = NULL, *record = NULL, **_2, *_10 = NULL, *_12 = NULL, **_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &connection, &related);



	nesting = 0;
	zephir_call_method_p1_noret(connection, "begin", (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	ZEPHIR_INIT_VAR(className);
	zephir_call_func_p1(className, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(manager);
	zephir_call_method(manager, this_ptr, "getmodelsmanager");
	zephir_is_iterable(related, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(name, _1, _0);
		ZEPHIR_GET_HVALUE(record, _2);
		ZEPHIR_INIT_NVAR(relation);
		zephir_call_method_p2_cache(relation, manager, "getrelationbyalias", &_3, className, name);
		if ((Z_TYPE_P(relation) == IS_OBJECT)) {
			ZEPHIR_INIT_NVAR(type);
			zephir_call_method_cache(type, relation, "gettype", &_4);
			if (ZEPHIR_IS_LONG(type, 0)) {
				if ((Z_TYPE_P(record) != IS_OBJECT)) {
					zephir_call_method_p1_cache_noret(connection, "rollback", &_5, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
					ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Only objects can be stored as part of belongs-to relations");
					return;
				}
				ZEPHIR_INIT_NVAR(columns);
				zephir_call_method_cache(columns, relation, "getfields", &_6);
				ZEPHIR_INIT_NVAR(referencedModel);
				zephir_call_method_cache(referencedModel, relation, "getreferencedmodel", &_7);
				ZEPHIR_INIT_NVAR(referencedFields);
				zephir_call_method_cache(referencedFields, relation, "getreferencedfields", &_8);
				if ((Z_TYPE_P(columns) == IS_ARRAY)) {
					zephir_call_method_p1_cache_noret(connection, "rollback", &_9, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
					ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Not implemented");
					return;
				}
				ZEPHIR_INIT_NVAR(_10);
				zephir_call_method_cache(_10, record, "save", &_11);
				if (!(zephir_is_true(_10))) {
					ZEPHIR_INIT_NVAR(_12);
					zephir_call_method_cache(_12, record, "getmessages", &_13);
					zephir_is_iterable(_12, &_15, &_14, 0, 0);
					for (
						; zend_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
						; zend_hash_move_forward_ex(_15, &_14)
					) {
						ZEPHIR_GET_HVALUE(message, _16);
						if ((Z_TYPE_P(record) == IS_OBJECT)) {
							zephir_call_method_p1_cache_noret(message, "setmodel", &_17, record);
						}
						zephir_call_method_p1_cache_noret(this_ptr, "appendmessage", &_18, message);
					}
					zephir_call_method_p1_cache_noret(connection, "rollback", &_19, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
					RETURN_MM_BOOL(0);
				}
				ZEPHIR_INIT_NVAR(_12);
				zephir_call_method_p1_cache(_12, record, "readattribute", &_20, referencedFields);
				zephir_update_property_zval_zval(this_ptr, columns, _12 TSRMLS_CC);
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Save the related records assigned in the has-one/has-many relations
 *
 * @param Phalcon\Db\AdapterInterface connection
 * @param Phalcon\Mvc\ModelInterface[] related
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, _postSaveRelatedRecords) {

	zend_function *_3 = NULL, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_8 = NULL, *_9 = NULL, *_10 = NULL, *_11 = NULL, *_15 = NULL, *_16 = NULL, *_17 = NULL, *_18 = NULL, *_19 = NULL, *_23 = NULL, *_24 = NULL, *_25 = NULL, *_26 = NULL, *_27 = NULL, *_29 = NULL, *_33 = NULL, *_34 = NULL, *_35 = NULL, *_36 = NULL, *_38 = NULL, *_42 = NULL, *_43 = NULL, *_44 = NULL, *_45 = NULL, *_48 = NULL;
	HashTable *_1, *_21, *_31, *_40;
	HashPosition _0, _20, _30, _39;
	zend_bool nesting, isThrough;
	zval *connection, *related, *className, *manager, *relation = NULL, *name = NULL, *record = NULL, *message = NULL, *columns = NULL, *referencedModel = NULL, *referencedFields = NULL, *relatedRecords = NULL, *value = NULL, *recordAfter = NULL, *intermediateModel = NULL, *intermediateFields = NULL, *intermediateValue = NULL, *intermediateModelName = NULL, *intermediateReferencedFields = NULL, **_2, *_4 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL, **_22, *_28 = NULL, **_32, *_37 = NULL, **_41, *_46 = NULL, *_47 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &connection, &related);



	nesting = 0;
	ZEPHIR_INIT_VAR(className);
	zephir_call_func_p1(className, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(manager);
	zephir_call_method(manager, this_ptr, "getmodelsmanager");
	zephir_is_iterable(related, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(name, _1, _0);
		ZEPHIR_GET_HVALUE(record, _2);
		ZEPHIR_INIT_NVAR(relation);
		zephir_call_method_p2_cache(relation, manager, "getrelationbyalias", &_3, className, name);
		if ((Z_TYPE_P(relation) == IS_OBJECT)) {
			ZEPHIR_INIT_NVAR(_4);
			zephir_call_method_cache(_4, relation, "gettype", &_5);
			if (ZEPHIR_IS_LONG(_4, 0)) {
				continue;
			}
			if ((Z_TYPE_P(record) != IS_OBJECT)) {
				if ((Z_TYPE_P(record) != IS_ARRAY)) {
					zephir_call_method_p1_cache_noret(connection, "rollback", &_6, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
					ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Only objects/arrays can be stored as part of has-many/has-one/has-many-to-many relations");
					return;
				}
			}
			ZEPHIR_INIT_NVAR(columns);
			zephir_call_method_cache(columns, relation, "getfields", &_7);
			ZEPHIR_INIT_NVAR(referencedModel);
			zephir_call_method_cache(referencedModel, relation, "getreferencedmodel", &_8);
			ZEPHIR_INIT_NVAR(referencedFields);
			zephir_call_method_cache(referencedFields, relation, "getreferencedfields", &_9);
			if ((Z_TYPE_P(columns) == IS_ARRAY)) {
				zephir_call_method_p1_cache_noret(connection, "rollback", &_10, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
				ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Not implemented");
				return;
			}
			if ((Z_TYPE_P(record) == IS_OBJECT)) {
				ZEPHIR_INIT_NVAR(relatedRecords);
				array_init(relatedRecords);
				zephir_array_append(&relatedRecords, record, 0);
			} else {
				ZEPHIR_CPY_WRT(relatedRecords, record);
			}
			ZEPHIR_OBS_NVAR(value);
			if (!(0)) {
				zephir_call_method_p1_cache_noret(connection, "rollback", &_11, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
				ZEPHIR_INIT_NVAR(_12);
				object_init_ex(_12, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_13);
				ZEPHIR_CONCAT_SV(_13, "The column '", columns);
				ZEPHIR_INIT_LNVAR(_14);
				ZEPHIR_CONCAT_VS(_14, _13, "' needs to be present in the model");
				zephir_call_method_p1_cache_noret(_12, "__construct", &_15, _14);
				zephir_throw_exception(_12 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_NVAR(_12);
			zephir_call_method_cache(_12, relation, "isthrough", &_16);
			isThrough = (zephir_get_boolval(_12)) ? 1 : 0;
			if (isThrough) {
				ZEPHIR_INIT_NVAR(intermediateModelName);
				zephir_call_method_cache(intermediateModelName, relation, "getintermediatemodel", &_17);
				ZEPHIR_INIT_NVAR(intermediateFields);
				zephir_call_method_cache(intermediateFields, relation, "getintermediatefields", &_18);
				ZEPHIR_INIT_NVAR(intermediateReferencedFields);
				zephir_call_method_cache(intermediateReferencedFields, relation, "getintermediatereferencedfields", &_19);
			}
			zephir_is_iterable(relatedRecords, &_21, &_20, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_21, (void**) &_22, &_20) == SUCCESS
				; zend_hash_move_forward_ex(_21, &_20)
			) {
				ZEPHIR_GET_HVALUE(recordAfter, _22);
				if (!(isThrough)) {
					zephir_call_method_p2_cache_noret(recordAfter, "writeattribute", &_23, referencedFields, value);
				} else {
					ZEPHIR_INIT_NVAR(intermediateModel);
					zephir_call_method_p2_cache(intermediateModel, manager, "load", &_24, intermediateModelName, ZEPHIR_GLOBAL(global_true));
					zephir_call_method_p2_cache_noret(intermediateModel, "writeattribute", &_25, intermediateFields, value);
					ZEPHIR_INIT_NVAR(intermediateValue);
					ZVAL_NULL(intermediateValue);
					zephir_call_method_p2_cache_noret(intermediateModel, "writeattribute", &_26, intermediateReferencedFields, intermediateValue);
					ZEPHIR_INIT_NVAR(_12);
					zephir_call_method_cache(_12, intermediateModel, "save", &_27);
					if (!(zephir_is_true(_12))) {
						ZEPHIR_INIT_NVAR(_28);
						zephir_call_method_cache(_28, intermediateModel, "getmessages", &_29);
						zephir_is_iterable(_28, &_31, &_30, 0, 0);
						for (
							; zend_hash_get_current_data_ex(_31, (void**) &_32, &_30) == SUCCESS
							; zend_hash_move_forward_ex(_31, &_30)
						) {
							ZEPHIR_GET_HVALUE(message, _32);
							if ((Z_TYPE_P(message) != IS_OBJECT)) {
								zephir_call_method_p1_cache_noret(message, "setmodel", &_33, record);
							}
							zephir_call_method_p1_cache_noret(this_ptr, "appendmessage", &_34, message);
						}
						zephir_call_method_p1_cache_noret(connection, "rollback", &_35, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
						RETURN_MM_BOOL(0);
					}
				}
				ZEPHIR_INIT_NVAR(_28);
				zephir_call_method_cache(_28, recordAfter, "save", &_36);
				if (!(zephir_is_true(_28))) {
					ZEPHIR_INIT_NVAR(_37);
					zephir_call_method_cache(_37, recordAfter, "getmessages", &_38);
					zephir_is_iterable(_37, &_40, &_39, 0, 0);
					for (
						; zend_hash_get_current_data_ex(_40, (void**) &_41, &_39) == SUCCESS
						; zend_hash_move_forward_ex(_40, &_39)
					) {
						ZEPHIR_GET_HVALUE(message, _41);
						if ((Z_TYPE_P(message) == IS_OBJECT)) {
							zephir_call_method_p1_cache_noret(message, "setmodel", &_42, record);
						}
						zephir_call_method_p1_cache_noret(this_ptr, "appendmessage", &_43, message);
					}
					zephir_call_method_p1_cache_noret(connection, "rollback", &_44, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
					RETURN_MM_BOOL(0);
				}
			}
		} else {
			if ((Z_TYPE_P(record) != IS_ARRAY)) {
				zephir_call_method_p1_cache_noret(connection, "rollback", &_45, (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
				ZEPHIR_INIT_NVAR(_4);
				object_init_ex(_4, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_13);
				ZEPHIR_CONCAT_SV(_13, "There are no defined relations for the model '", className);
				ZEPHIR_INIT_LNVAR(_14);
				ZEPHIR_CONCAT_VS(_14, _13, "' using alias '");
				ZEPHIR_INIT_LNVAR(_46);
				concat_function(_46, _14, name TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_47);
				ZEPHIR_CONCAT_VS(_47, _46, "'");
				zephir_call_method_p1_cache_noret(_4, "__construct", &_48, _47);
				zephir_throw_exception(_4 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	zephir_call_method_p1_noret(connection, "commit", (nesting ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	RETURN_MM_BOOL(1);

}

/**
 * Inserts or updates a model instance. Returning true on success or false otherwise.
 *
 *<code>
 *	//Creating a new robot
 *	$robot = new Robots();
 *	$robot->type = 'mechanical';
 *	$robot->name = 'Astro Boy';
 *	$robot->year = 1952;
 *	$robot->save();
 *
 *	//Updating a robot name
 *	$robot = Robots::findFirst("id=100");
 *	$robot->name = "Biomass";
 *	$robot->save();
 *</code>
 *
 * @param array data
 * @param array whiteList
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, save) {

	HashTable *_1;
	HashPosition _0;
	zval *data = NULL, *whiteList = NULL, *metaData, *attribute = NULL, *attributes = NULL, *related, *schema, *possibleSetter = NULL, *value = NULL, *writeConnection, *readConnection, *source, *table = NULL, *identityField, *exists, *success = NULL, **_2, *_3 = NULL, *_4, *_5, *_6, *_7 = NULL, *_8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &data, &whiteList);

	if (!data) {
		ZEPHIR_CPY_WRT(data, ZEPHIR_GLOBAL(global_null));
	}
	if (!whiteList) {
		ZEPHIR_CPY_WRT(whiteList, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	if ((Z_TYPE_P(data) != IS_NULL)) {
		if ((Z_TYPE_P(data) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data passed to save() must be an array");
			return;
		}
		ZEPHIR_INIT_VAR(attributes);
		zephir_call_method_p1(attributes, metaData, "getcolumnmap", this_ptr);
		if ((Z_TYPE_P(attributes) == IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(attributes);
			zephir_call_method_p1(attributes, metaData, "getattributes", this_ptr);
		}
		zephir_is_iterable(attributes, &_1, &_0, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
			; zend_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(attribute, _2);
			ZEPHIR_OBS_NVAR(value);
			if (zephir_array_isset_fetch(&value, data, attribute TSRMLS_CC)) {
				if ((Z_TYPE_P(whiteList) == IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(_3);
					zephir_call_func_p2(_3, "in_array", attribute, whiteList);
					if (!(zephir_is_true(_3))) {
						continue;
					}
				}
				ZEPHIR_INIT_NVAR(possibleSetter);
				ZEPHIR_CONCAT_SV(possibleSetter, "set", attribute);
				if ((zephir_method_exists(this_ptr, possibleSetter TSRMLS_CC)  == SUCCESS)) {
					zephir_call_method_zval_p1_noret(this_ptr, possibleSetter, value);
				} else {
					zephir_update_property_zval_zval(this_ptr, attribute, value TSRMLS_CC);
				}
			}
		}
	}
	ZEPHIR_INIT_VAR(writeConnection);
	zephir_call_method(writeConnection, this_ptr, "getwriteconnection");
	related = zephir_fetch_nproperty_this(this_ptr, SL("_related"), PH_NOISY_CC);
	if ((Z_TYPE_P(related) == IS_ARRAY)) {
		ZEPHIR_INIT_NVAR(_3);
		zephir_call_method_p2(_3, this_ptr, "_presaverelatedrecords", writeConnection, related);
		if (ZEPHIR_IS_FALSE(_3)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_VAR(schema);
	zephir_call_method(schema, this_ptr, "getschema");
	ZEPHIR_INIT_VAR(source);
	zephir_call_method(source, this_ptr, "getsource");
	if (zephir_is_true(schema)) {
		ZEPHIR_INIT_VAR(table);
		array_init(table);
		zephir_array_append(&table, schema, 0);
		zephir_array_append(&table, source, 0);
	} else {
		ZEPHIR_CPY_WRT(table, source);
	}
	ZEPHIR_INIT_VAR(readConnection);
	zephir_call_method(readConnection, this_ptr, "getreadconnection");
	ZEPHIR_INIT_VAR(exists);
	zephir_call_method_p3(exists, this_ptr, "_exists", metaData, readConnection, table);
	if (zephir_is_true(exists)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 2);
		zephir_update_property_this(this_ptr, SL("_operationMade"), _4 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 1);
		zephir_update_property_this(this_ptr, SL("_operationMade"), _4 TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(_5);
	array_init(_5);
	zephir_update_property_this(this_ptr, SL("_errorMessages"), _5 TSRMLS_CC);
	ZEPHIR_INIT_VAR(identityField);
	zephir_call_method_p1(identityField, metaData, "getidentityfield", this_ptr);
	ZEPHIR_INIT_VAR(_6);
	zephir_call_method_p3(_6, this_ptr, "_presave", metaData, exists, identityField);
	if (ZEPHIR_IS_FALSE(_6)) {
		if ((Z_TYPE_P(related) == IS_ARRAY)) {
			zephir_call_method_p1_noret(writeConnection, "rollback", ZEPHIR_GLOBAL(global_false));
		}
		ZEPHIR_INIT_VAR(_7);
		ZVAL_STRING(_7, "orm.exception_on_failed_save", 1);
		ZEPHIR_INIT_VAR(_8);
		zephir_call_func_p1(_8, "globals_get", _7);
		if (zephir_is_true(_8)) {
			ZEPHIR_INIT_NVAR(_7);
			object_init_ex(_7, phalcon_mvc_model_validationfailed_ce);
			_4 = zephir_fetch_nproperty_this(this_ptr, SL("_errorMessages"), PH_NOISY_CC);
			zephir_call_method_p2_noret(_7, "__construct", this_ptr, _4);
			zephir_throw_exception(_7 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(success);
	if (zephir_is_true(exists)) {
		zephir_call_method_p3(success, this_ptr, "_dolowupdate", metaData, writeConnection, table);
	} else {
		zephir_call_method_p4(success, this_ptr, "_dolowinsert", metaData, writeConnection, table, identityField);
	}
	if (zephir_is_true(success)) {
		ZEPHIR_INIT_ZVAL_NREF(_4);
		ZVAL_LONG(_4, 0);
		zephir_update_property_this(this_ptr, SL("_dirtyState"), _4 TSRMLS_CC);
	}
	ZEPHIR_INIT_NVAR(_7);
	ZVAL_STRING(_7, "orm.events", 1);
	ZEPHIR_INIT_NVAR(_8);
	zephir_call_func_p1(_8, "globals_get", _7);
	if (zephir_is_true(_8)) {
		ZEPHIR_INIT_NVAR(_7);
		zephir_call_method_p2(_7, this_ptr, "_postsave", success, exists);
		ZEPHIR_CPY_WRT(success, _7);
	}
	if ((Z_TYPE_P(related) == IS_ARRAY)) {
		if (ZEPHIR_IS_FALSE(success)) {
			zephir_call_method_p1_noret(writeConnection, "rollback", ZEPHIR_GLOBAL(global_false));
			RETURN_MM_BOOL(0);
		}
		ZEPHIR_INIT_NVAR(_7);
		zephir_call_method_p2(_7, this_ptr, "_postsaverelatedrecords", writeConnection, related);
		if (ZEPHIR_IS_FALSE(_7)) {
			RETURN_MM_BOOL(0);
		}
	}
	RETURN_CCTOR(success);

}

/**
 * Inserts a model instance. If the instance already exists in the persistance it will throw an exception
 * Returning true on success or false otherwise.
 *
 *<code>
 *	//Creating a new robot
 *	$robot = new Robots();
 *	$robot->type = 'mechanical';
 *	$robot->name = 'Astro Boy';
 *	$robot->year = 1952;
 *	$robot->create();
 *
 *  //Passing an array to create
 *  $robot = new Robots();
 *  $robot->create(array(
 *      'type' => 'mechanical',
 *      'name' => 'Astroy Boy',
 *      'year' => 1952
 *  ));
 *</code>
 *
 * @param array data
 * @param array whiteList
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, create) {

	zend_function *_8 = NULL;
	HashTable *_3;
	HashPosition _2;
	zval *data = NULL, *whiteList = NULL, *metaData, *attribute = NULL, *possibleSetter = NULL, *value = NULL, *columnMap, *attributeField = NULL, *_0 = NULL, *_1 = NULL, **_4, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_9;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &data, &whiteList);

	if (!data) {
		ZEPHIR_CPY_WRT(data, ZEPHIR_GLOBAL(global_null));
	}
	if (!whiteList) {
		ZEPHIR_CPY_WRT(whiteList, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	if ((Z_TYPE_P(data) != IS_NULL)) {
		if ((Z_TYPE_P(data) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data passed to create() must be an array");
			return;
		}
		ZEPHIR_INIT_VAR(columnMap);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "orm.column_renaming", 1);
		ZEPHIR_INIT_VAR(_1);
		zephir_call_func_p1(_1, "globals_get", _0);
		if (zephir_is_true(_1)) {
			zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
		} else {
			ZVAL_NULL(columnMap);
		}
		ZEPHIR_INIT_NVAR(_0);
		zephir_call_method_p1(_0, metaData, "getattributes", this_ptr);
		zephir_is_iterable(_0, &_3, &_2, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
			; zend_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(attribute, _4);
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, attribute TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_5);
					object_init_ex(_5, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_SV(_6, "Column '", attribute);
					ZEPHIR_INIT_LNVAR(_7);
					ZEPHIR_CONCAT_VS(_7, _6, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_5, "__construct", &_8, _7);
					zephir_throw_exception(_5 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, attribute);
			}
			ZEPHIR_OBS_NVAR(value);
			if (zephir_array_isset_fetch(&value, data, attributeField TSRMLS_CC)) {
				if ((Z_TYPE_P(whiteList) == IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(_5);
					zephir_call_func_p2(_5, "in_array", attributeField, whiteList);
					if (!(zephir_is_true(_5))) {
						continue;
					}
				}
				ZEPHIR_INIT_NVAR(possibleSetter);
				ZEPHIR_CONCAT_SV(possibleSetter, "set", attributeField);
				if ((zephir_method_exists(this_ptr, possibleSetter TSRMLS_CC)  == SUCCESS)) {
					zephir_call_method_zval_p1_noret(this_ptr, possibleSetter, value);
				} else {
					zephir_update_property_zval_zval(this_ptr, attributeField, value TSRMLS_CC);
				}
			}
		}
	}
	ZEPHIR_INIT_NVAR(_0);
	ZEPHIR_INIT_NVAR(_1);
	zephir_call_method(_1, this_ptr, "getreadconnection");
	zephir_call_method_p2(_0, this_ptr, "_exists", metaData, _1);
	if (zephir_is_true(_0)) {
		ZEPHIR_INIT_NVAR(_5);
		array_init(_5);
		ZEPHIR_INIT_VAR(_9);
		object_init_ex(_9, phalcon_mvc_model_message_ce);
		zephir_array_append(&_5, _9, 0);
		zephir_update_property_this(this_ptr, SL("_errorMessages"), _5 TSRMLS_CC);
		RETURN_MM_BOOL(0);
	}
	zephir_call_method(return_value, this_ptr, "save");
	RETURN_MM();

}

/**
 * Updates a model instance. If the instance doesn't exist in the persistance it will throw an exception
 * Returning true on success or false otherwise.
 *
 *<code>
 *	//Updating a robot name
 *	$robot = Robots::findFirst("id=100");
 *	$robot->name = "Biomass";
 *	$robot->update();
 *</code>
 *
 * @param array data
 * @param array whiteList
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, update) {

	zend_function *_8 = NULL;
	HashTable *_3;
	HashPosition _2;
	zval *data = NULL, *whiteList = NULL, *metaData, *columnMap, *attribute = NULL, *attributeField = NULL, *possibleSetter = NULL, *value = NULL, *_0 = NULL, *_1 = NULL, **_4, *_5 = NULL, *_6 = NULL, *_7 = NULL, *_9, *_10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &data, &whiteList);

	if (!data) {
		ZEPHIR_CPY_WRT(data, ZEPHIR_GLOBAL(global_null));
	}
	if (!whiteList) {
		ZEPHIR_CPY_WRT(whiteList, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(metaData);
	ZVAL_NULL(metaData);
	if ((Z_TYPE_P(data) != IS_NULL)) {
		if ((Z_TYPE_P(data) != IS_ARRAY)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Data passed to update() must be an array");
			return;
		}
		ZEPHIR_INIT_BNVAR(metaData);
		zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
		ZEPHIR_INIT_VAR(columnMap);
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "orm.column_renaming", 1);
		ZEPHIR_INIT_VAR(_1);
		zephir_call_func_p1(_1, "globals_get", _0);
		if (zephir_is_true(_1)) {
			zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
		} else {
			ZVAL_NULL(columnMap);
		}
		ZEPHIR_INIT_NVAR(_0);
		zephir_call_method_p1(_0, metaData, "getattributes", this_ptr);
		zephir_is_iterable(_0, &_3, &_2, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
			; zend_hash_move_forward_ex(_3, &_2)
		) {
			ZEPHIR_GET_HVALUE(attribute, _4);
			if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
				ZEPHIR_OBS_NVAR(attributeField);
				if (!(zephir_array_isset_fetch(&attributeField, columnMap, attribute TSRMLS_CC))) {
					ZEPHIR_INIT_NVAR(_5);
					object_init_ex(_5, phalcon_mvc_model_exception_ce);
					ZEPHIR_INIT_LNVAR(_6);
					ZEPHIR_CONCAT_SV(_6, "Column '", attribute);
					ZEPHIR_INIT_LNVAR(_7);
					ZEPHIR_CONCAT_VS(_7, _6, "' isn't part of the column map");
					zephir_call_method_p1_cache_noret(_5, "__construct", &_8, _7);
					zephir_throw_exception(_5 TSRMLS_CC);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} else {
				ZEPHIR_CPY_WRT(attributeField, attribute);
			}
			ZEPHIR_OBS_NVAR(value);
			if (zephir_array_isset_fetch(&value, data, attributeField TSRMLS_CC)) {
				if ((Z_TYPE_P(whiteList) == IS_ARRAY)) {
					ZEPHIR_INIT_NVAR(_5);
					zephir_call_func_p2(_5, "in_array", attributeField, whiteList);
					if (!(zephir_is_true(_5))) {
						continue;
					}
				}
				ZEPHIR_INIT_NVAR(possibleSetter);
				ZEPHIR_CONCAT_SV(possibleSetter, "set", attributeField);
				if ((zephir_method_exists(this_ptr, possibleSetter TSRMLS_CC)  == SUCCESS)) {
					zephir_call_method_zval_p1_noret(this_ptr, possibleSetter, value);
				} else {
					zephir_update_property_zval_zval(this_ptr, attributeField, value TSRMLS_CC);
				}
			}
		}
	}
	_9 = zephir_fetch_nproperty_this(this_ptr, SL("_dirtyState"), PH_NOISY_CC);
	if (zephir_is_true(_9)) {
		if ((Z_TYPE_P(metaData) == IS_NULL)) {
			ZEPHIR_INIT_BNVAR(metaData);
			zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
		}
		ZEPHIR_INIT_NVAR(_0);
		ZEPHIR_INIT_NVAR(_1);
		zephir_call_method(_1, this_ptr, "getreadconnection");
		zephir_call_method_p2(_0, this_ptr, "_exists", metaData, _1);
		if (zephir_is_true(_0)) {
			ZEPHIR_INIT_NVAR(_5);
			array_init(_5);
			ZEPHIR_INIT_VAR(_10);
			object_init_ex(_10, phalcon_mvc_model_message_ce);
			zephir_array_append(&_5, _10, 0);
			zephir_update_property_this(this_ptr, SL("_errorMessages"), _5 TSRMLS_CC);
			RETURN_MM_BOOL(0);
		}
	}
	zephir_call_method(return_value, this_ptr, "save");
	RETURN_MM();

}

/**
 * Deletes a model instance. Returning true on success or false otherwise.
 *
 * <code>
 *$robot = Robots::findFirst("id=100");
 *$robot->delete();
 *
 *foreach (Robots::find("type = 'mechanical'") as $robot) {
 *   $robot->delete();
 *}
 * </code>
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, delete) {

	zend_function *_11 = NULL, *_12 = NULL, *_13 = NULL, *_14 = NULL;
	HashTable *_7;
	HashPosition _6;
	zval *metaData, *writeConnection, *values, *bindTypes, *primaryKeys, *bindDataTypes, *columnMap, *attributeField = NULL, *conditions, *primaryKey = NULL, *bindType = NULL, *value = NULL, *schema, *source, *table = NULL, *success, *_0, *_1, *_2, *_3, *_4 = NULL, *_5, **_8, *_9 = NULL, *_10 = NULL, *_15, *_16, *_17 = NULL, *_18, _19, *_20, *_21, *_22;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(writeConnection);
	zephir_call_method(writeConnection, this_ptr, "getwriteconnection");
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, 3);
	zephir_update_property_this(this_ptr, SL("_operationMade"), _0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_1);
	array_init(_1);
	zephir_update_property_this(this_ptr, SL("_errorMessages"), _1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_STRING(_2, "orm.virtual_foreign_keys", 1);
	ZEPHIR_INIT_VAR(_3);
	zephir_call_func_p1(_3, "globals_get", _2);
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_BNVAR(_2);
		zephir_call_method(_2, this_ptr, "_checkforeignkeysreverserestrict");
		if (ZEPHIR_IS_FALSE(_2)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_VAR(values);
	array_init(values);
	ZEPHIR_INIT_VAR(bindTypes);
	array_init(bindTypes);
	ZEPHIR_INIT_VAR(conditions);
	array_init(conditions);
	ZEPHIR_INIT_VAR(primaryKeys);
	zephir_call_method_p1(primaryKeys, metaData, "getprimarykeyattributes", this_ptr);
	ZEPHIR_INIT_VAR(bindDataTypes);
	zephir_call_method_p1(bindDataTypes, metaData, "getbindtypes", this_ptr);
	ZEPHIR_INIT_VAR(columnMap);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "orm.column_renaming", 1);
	ZEPHIR_INIT_VAR(_5);
	zephir_call_func_p1(_5, "globals_get", _4);
	if (zephir_is_true(_5)) {
		zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
	} else {
		ZVAL_NULL(columnMap);
	}
	if (!(zephir_fast_count_int(primaryKeys TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "A primary key must be defined in the model in order to perform the operation");
		return;
	}
	zephir_is_iterable(primaryKeys, &_7, &_6, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
		; zend_hash_move_forward_ex(_7, &_6)
	) {
		ZEPHIR_GET_HVALUE(primaryKey, _8);
		ZEPHIR_OBS_NVAR(bindType);
		if (!(zephir_array_isset_fetch(&bindType, bindDataTypes, primaryKey TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_4);
			object_init_ex(_4, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_LNVAR(_9);
			ZEPHIR_CONCAT_SV(_9, "Column '", primaryKey);
			ZEPHIR_INIT_LNVAR(_10);
			ZEPHIR_CONCAT_VS(_10, _9, "' have not defined a bind data type");
			zephir_call_method_p1_cache_noret(_4, "__construct", &_11, _10);
			zephir_throw_exception(_4 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
			ZEPHIR_OBS_NVAR(attributeField);
			if (!(zephir_array_isset_fetch(&attributeField, columnMap, primaryKey TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_4);
				object_init_ex(_4, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_9);
				ZEPHIR_CONCAT_SV(_9, "Column '", primaryKey);
				ZEPHIR_INIT_LNVAR(_10);
				ZEPHIR_CONCAT_VS(_10, _9, "' isn't part of the column map");
				zephir_call_method_p1_cache_noret(_4, "__construct", &_12, _10);
				zephir_throw_exception(_4 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(attributeField, primaryKey);
		}
		ZEPHIR_OBS_NVAR(value);
		if (!(0)) {
			ZEPHIR_INIT_NVAR(_4);
			object_init_ex(_4, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_LNVAR(_9);
			ZEPHIR_CONCAT_SV(_9, "Cannot delete the record because the primary key attribute: '", attributeField);
			ZEPHIR_INIT_LNVAR(_10);
			ZEPHIR_CONCAT_VS(_10, _9, "' wasn't set");
			zephir_call_method_p1_cache_noret(_4, "__construct", &_13, _10);
			zephir_throw_exception(_4 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_array_append(&values, value, PH_SEPARATE);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_method_p1_cache(_4, writeConnection, "escapeidentifier", &_14, primaryKey);
		ZEPHIR_INIT_LNVAR(_9);
		ZEPHIR_CONCAT_VS(_9, _4, " = ?");
		zephir_array_append(&conditions, _9, PH_SEPARATE);
		zephir_array_append(&bindTypes, bindType, PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(_15);
	ZVAL_STRING(_15, "orm.events", 1);
	ZEPHIR_INIT_VAR(_16);
	zephir_call_func_p1(_16, "globals_get", _15);
	if (zephir_is_true(_16)) {
		zephir_update_property_this(this_ptr, SL("_skipped"), ZEPHIR_GLOBAL(global_false) TSRMLS_CC);
		ZEPHIR_INIT_BNVAR(_15);
		ZEPHIR_INIT_VAR(_17);
		ZVAL_STRING(_17, "beforeDelete", 1);
		zephir_call_method_p1(_15, this_ptr, "fireeventcancel", _17);
		if (ZEPHIR_IS_FALSE(_15)) {
			RETURN_MM_BOOL(0);
		} else {
			_18 = zephir_fetch_nproperty_this(this_ptr, SL("_skipped"), PH_NOISY_CC);
			if (ZEPHIR_IS_TRUE(_18)) {
				RETURN_MM_BOOL(1);
			}
		}
	}
	ZEPHIR_INIT_VAR(schema);
	zephir_call_method(schema, this_ptr, "getschema");
	ZEPHIR_INIT_VAR(source);
	zephir_call_method(source, this_ptr, "getsource");
	if (zephir_is_true(schema)) {
		ZEPHIR_INIT_VAR(table);
		array_init(table);
		zephir_array_append(&table, schema, 0);
		zephir_array_append(&table, source, 0);
	} else {
		ZEPHIR_CPY_WRT(table, source);
	}
	ZEPHIR_SINIT_VAR(_19);
	ZVAL_STRING(&_19, " AND ", 0);
	ZEPHIR_INIT_NVAR(_17);
	zephir_call_func_p2(_17, "join", &_19, conditions);
	ZEPHIR_INIT_VAR(success);
	zephir_call_method_p4(success, writeConnection, "delete", table, _17, values, bindTypes);
	ZEPHIR_INIT_VAR(_20);
	ZVAL_STRING(_20, "orm.virtual_foreign_keys", 1);
	ZEPHIR_INIT_VAR(_21);
	zephir_call_func_p1(_21, "globals_get", _20);
	if (zephir_is_true(_21)) {
		ZEPHIR_INIT_BNVAR(_20);
		zephir_call_method(_20, this_ptr, "_checkforeignkeysreversecascade");
		if (ZEPHIR_IS_FALSE(_20)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_INIT_NVAR(_17);
	ZVAL_STRING(_17, "orm.events", 1);
	ZEPHIR_INIT_VAR(_22);
	zephir_call_func_p1(_22, "globals_get", _17);
	if (zephir_is_true(_22)) {
		if (zephir_is_true(success)) {
			ZEPHIR_INIT_NVAR(_17);
			ZVAL_STRING(_17, "afterDelete", 1);
			zephir_call_method_p1_noret(this_ptr, "fireevent", _17);
		}
	}
	ZEPHIR_INIT_ZVAL_NREF(_18);
	ZVAL_LONG(_18, 2);
	zephir_update_property_this(this_ptr, SL("_dirtyState"), _18 TSRMLS_CC);
	RETURN_CCTOR(success);

}

/**
 * Returns the type of the latest operation performed by the ORM
 * Returns one of the OP_* class constants
 *
 * @return int
 */
PHP_METHOD(Phalcon_Mvc_Model, getOperationMade) {


	RETURN_MEMBER(this_ptr, "_operationMade");

}

/**
 * Refreshes the model attributes re-querying the record from the database
 */
PHP_METHOD(Phalcon_Mvc_Model, refresh) {

	HashTable *_3;
	HashPosition _2;
	zval *metaData, *readConnection, *schema, *source, *table = NULL, *uniqueKey = NULL, *uniqueParams, *dialect, *row, *fields, *attribute = NULL, *_0, *_1 = NULL, **_4, *_5 = NULL, *_6, *_7;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dirtyState"), PH_NOISY_CC);
	if (!ZEPHIR_IS_LONG(_0, 0)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The record cannot be refreshed because it does not exist or is deleted");
		return;
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(readConnection);
	zephir_call_method(readConnection, this_ptr, "getreadconnection");
	ZEPHIR_INIT_VAR(schema);
	zephir_call_method(schema, this_ptr, "getschema");
	ZEPHIR_INIT_VAR(source);
	zephir_call_method(source, this_ptr, "getsource");
	if (zephir_is_true(schema)) {
		ZEPHIR_INIT_VAR(table);
		array_init(table);
		zephir_array_append(&table, schema, 0);
		zephir_array_append(&table, source, 0);
	} else {
		ZEPHIR_CPY_WRT(table, source);
	}
	ZEPHIR_OBS_VAR(uniqueKey);
	zephir_read_property_this(&uniqueKey, this_ptr, SL("_uniqueKey"), PH_NOISY_CC);
	if (!(zephir_is_true(uniqueKey))) {
		ZEPHIR_INIT_VAR(_1);
		zephir_call_method_p3(_1, this_ptr, "_exists", metaData, readConnection, table);
		if (zephir_is_true(_1)) {
			ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The record cannot be refreshed because it does not exist or is deleted");
			return;
		}
		ZEPHIR_OBS_NVAR(uniqueKey);
		zephir_read_property_this(&uniqueKey, this_ptr, SL("_uniqueKey"), PH_NOISY_CC);
	}
	uniqueParams = zephir_fetch_nproperty_this(this_ptr, SL("_uniqueParams"), PH_NOISY_CC);
	if ((Z_TYPE_P(uniqueParams) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The record cannot be refreshed because it does not exist or is deleted");
		return;
	}
	ZEPHIR_INIT_VAR(fields);
	array_init(fields);
	ZEPHIR_INIT_NVAR(_1);
	zephir_call_method_p1(_1, metaData, "getattributes", this_ptr);
	zephir_is_iterable(_1, &_3, &_2, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_3, (void**) &_4, &_2) == SUCCESS
		; zend_hash_move_forward_ex(_3, &_2)
	) {
		ZEPHIR_GET_HVALUE(attribute, _4);
		ZEPHIR_INIT_NVAR(_5);
		array_init(_5);
		zephir_array_append(&_5, attribute, 0);
		zephir_array_append(&fields, _5, PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(dialect);
	zephir_call_method(dialect, readConnection, "getdialect");
	ZEPHIR_INIT_NVAR(_1);
	ZEPHIR_INIT_NVAR(_5);
	array_init(_5);
	zephir_array_update_string(&_5, SL("columns"), &fields, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_6);
	zephir_call_method_p1(_6, readConnection, "escapeidentifier", table);
	zephir_array_update_string(&_5, SL("tables"), &_6, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_5, SL("where"), &uniqueKey, PH_COPY | PH_SEPARATE);
	zephir_call_method_p1(_1, dialect, "select", _5);
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("_uniqueTypes"), PH_NOISY_CC);
	ZEPHIR_INIT_BNVAR(_6);
	ZVAL_LONG(_6, 1);
	ZEPHIR_INIT_VAR(row);
	zephir_call_method_p4(row, readConnection, "fetchone", _1, _6, uniqueParams, _7);
	if ((Z_TYPE_P(row) == IS_ARRAY)) {
		ZEPHIR_INIT_BNVAR(_6);
		zephir_call_method_p1(_6, metaData, "getcolumnmap", this_ptr);
		zephir_call_method_p2_noret(this_ptr, "assign", row, _6);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Skips the current operation forcing a success state
 *
 * @param boolean skip
 */
PHP_METHOD(Phalcon_Mvc_Model, skipOperation) {

	zval *skip_param = NULL, *_0;
	zend_bool skip;

	zephir_fetch_params(0, 1, 0, &skip_param);

		skip = zephir_get_boolval(skip_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_BOOL(_0, skip);
	zephir_update_property_this(this_ptr, SL("_skipped"), _0 TSRMLS_CC);

}

/**
 * Reads an attribute value by its name
 *
 * <code>
 * echo $robot->readAttribute('name');
 * </code>
 *
 * @param string attribute
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, readAttribute) {

	zval *attribute_param = NULL;
	zval *attribute = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &attribute_param);

		zephir_get_strval(attribute, attribute_param);


	if (0) {
		RETURN_MM_NULL();
	}
	RETURN_MM_NULL();

}

/**
 * Writes an attribute value by its name
 *
 * <code>
 * 	$robot->writeAttribute('name', 'Rosey');
 * </code>
 *
 * @param string attribute
 * @param mixed value
 */
PHP_METHOD(Phalcon_Mvc_Model, writeAttribute) {

	zval *attribute_param = NULL, *value;
	zval *attribute = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &attribute_param, &value);

		zephir_get_strval(attribute, attribute_param);


	zephir_update_property_zval_zval(this_ptr, attribute, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets a list of attributes that must be skipped from the
 * generated INSERT/UPDATE statement
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->skipAttributes(array('price'));
 *   }
 *
 *}
 *</code>
 *
 * @param array attributes
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributes) {

	HashTable *_1;
	HashPosition _0;
	zval *attributes, *keysAttributes, *metaData, *attribute = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &attributes);



	if ((Z_TYPE_P(attributes) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Attributes must be an array");
		return;
	}
	ZEPHIR_INIT_VAR(keysAttributes);
	array_init(keysAttributes);
	zephir_is_iterable(attributes, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(attribute, _2);
		zephir_array_update_zval(&keysAttributes, attribute, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	zephir_call_method_p2_noret(metaData, "setautomaticcreateattributes", this_ptr, keysAttributes);
	zephir_call_method_p2_noret(metaData, "setautomaticupdateattributes", this_ptr, keysAttributes);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets a list of attributes that must be skipped from the
 * generated INSERT statement
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->skipAttributesOnCreate(array('created_at'));
 *   }
 *
 *}
 *</code>
 *
 * @param array attributes
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributesOnCreate) {

	HashTable *_1;
	HashPosition _0;
	zval *attributes, *keysAttributes, *metaData, *attribute = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &attributes);



	if ((Z_TYPE_P(attributes) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Attributes must be an array");
		return;
	}
	ZEPHIR_INIT_VAR(keysAttributes);
	array_init(keysAttributes);
	zephir_is_iterable(attributes, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(attribute, _2);
		zephir_array_update_zval(&keysAttributes, attribute, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	zephir_call_method_p2_noret(metaData, "setautomaticcreateattributes", this_ptr, keysAttributes);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets a list of attributes that must be skipped from the
 * generated UPDATE statement
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->skipAttributesOnUpdate(array('modified_in'));
 *   }
 *
 *}
 *</code>
 *
 * @param array attributes
 */
PHP_METHOD(Phalcon_Mvc_Model, skipAttributesOnUpdate) {

	HashTable *_1;
	HashPosition _0;
	zval *attributes, *keysAttributes, *metaData, *attribute = NULL, **_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &attributes);



	if ((Z_TYPE_P(attributes) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Attributes must be an array");
		return;
	}
	ZEPHIR_INIT_VAR(keysAttributes);
	array_init(keysAttributes);
	zephir_is_iterable(attributes, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(attribute, _2);
		zephir_array_update_zval(&keysAttributes, attribute, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	zephir_call_method_p2_noret(metaData, "setautomaticupdateattributes", this_ptr, keysAttributes);
	ZEPHIR_MM_RESTORE();

}

/**
 * Setup a 1-1 relation between two models
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->hasOne('id', 'RobotsDescription', 'robots_id');
 *   }
 *
 *}
 *</code>
 *
 * @param	mixed fields
 * @param	string referenceModel
 * @param	mixed referencedFields
 * @param   array options
 * @return  Phalcon\Mvc\Model\Relation
 */
PHP_METHOD(Phalcon_Mvc_Model, hasOne) {

	zval *referenceModel = NULL;
	zval *fields, *referenceModel_param = NULL, *referencedFields, *options = NULL, *manager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &fields, &referenceModel_param, &referencedFields, &options);

		zephir_get_strval(referenceModel, referenceModel_param);
	if (!options) {
		ZEPHIR_CPY_WRT(options, ZEPHIR_GLOBAL(global_null));
	}


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p5(return_value, manager, "addhasone", this_ptr, fields, referenceModel, referencedFields, options);
	RETURN_MM();

}

/**
 * Setup a relation reverse 1-1  between two models
 *
 *<code>
 *<?php
 *
 *class RobotsParts extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->belongsTo('robots_id', 'Robots', 'id');
 *   }
 *
 *}
 *</code>
 *
 * @param	mixed fields
 * @param	string referenceModel
 * @param	mixed referencedFields
 * @param   array options
 * @return  Phalcon\Mvc\Model\Relation
 */
PHP_METHOD(Phalcon_Mvc_Model, belongsTo) {

	zval *fields, *referenceModel, *referencedFields, *options = NULL, *manager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &fields, &referenceModel, &referencedFields, &options);

	if (!options) {
		ZEPHIR_CPY_WRT(options, ZEPHIR_GLOBAL(global_null));
	}


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p5(return_value, manager, "addbelongsto", this_ptr, fields, referenceModel, referencedFields, options);
	RETURN_MM();

}

/**
 * Setup a relation 1-n between two models
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       $this->hasMany('id', 'RobotsParts', 'robots_id');
 *   }
 *
 *}
 *</code>
 *
 * @param	mixed fields
 * @param	string referenceModel
 * @param	mixed referencedFields
 * @param   array options
 * @return  Phalcon\Mvc\Model\Relation
 */
PHP_METHOD(Phalcon_Mvc_Model, hasMany) {

	zval *referenceModel = NULL;
	zval *fields, *referenceModel_param = NULL, *referencedFields, *options = NULL, *manager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &fields, &referenceModel_param, &referencedFields, &options);

		zephir_get_strval(referenceModel, referenceModel_param);
	if (!options) {
		ZEPHIR_CPY_WRT(options, ZEPHIR_GLOBAL(global_null));
	}


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p5(return_value, manager, "addhasmany", this_ptr, fields, referenceModel, referencedFields, options);
	RETURN_MM();

}

/**
 * Setup a relation n-n between two models through an intermediate relation
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *       //Setup a many-to-many relation to Parts through RobotsParts
 *       $this->hasManyToMany(
 *			'id',
 *			'RobotsParts',
 *			'robots_id',
 *			'parts_id',
 *			'Parts',
 *			'id'
 *		);
 *   }
 *
 *}
 *</code>
 *
 * @param	string|array fields
 * @param	string intermediateModel
 * @param	string|array intermediateFields
 * @param	string|array intermediateReferencedFields
 * @param	string referencedModel
 * @param   string|array referencedFields
 * @param   array options
 * @return  Phalcon\Mvc\Model\Relation
 */
PHP_METHOD(Phalcon_Mvc_Model, hasManyToMany) {

	zval *intermediateModel = NULL, *referenceModel = NULL;
	zval *fields, *intermediateModel_param = NULL, *intermediateFields, *intermediateReferencedFields, *referenceModel_param = NULL, *referencedFields, *options = NULL, *manager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 6, 1, &fields, &intermediateModel_param, &intermediateFields, &intermediateReferencedFields, &referenceModel_param, &referencedFields, &options);

		zephir_get_strval(intermediateModel, intermediateModel_param);
		zephir_get_strval(referenceModel, referenceModel_param);
	if (!options) {
		ZEPHIR_CPY_WRT(options, ZEPHIR_GLOBAL(global_null));
	}


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p8(return_value, manager, "addhasmanytomany", this_ptr, fields, intermediateModel, intermediateFields, intermediateReferencedFields, referenceModel, referencedFields, options);
	RETURN_MM();

}

/**
 * Setups a behavior in a model
 *
 *<code>
 *<?php
 *
 *use Phalcon\Mvc\Model\Behavior\Timestampable;
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *		$this->addBehavior(new Timestampable(array(
 *			'onCreate' => array(
 *				'field' => 'created_at',
 *				'format' => 'Y-m-d'
 *			)
 *		)));
 *   }
 *
 *}
 *</code>
 *
 * @param Phalcon\Mvc\Model\BehaviorInterface behavior
 */
PHP_METHOD(Phalcon_Mvc_Model, addBehavior) {

	zval *behavior, *manager;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &behavior);



	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p2_noret(manager, "addbehavior", this_ptr, behavior);
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets if the model must keep the original record snapshot in memory
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *		$this->keepSnapshots(true);
 *   }
 *
 *}
 *</code>
 *
 * @param boolean keepSnapshots
 */
PHP_METHOD(Phalcon_Mvc_Model, keepSnapshots) {

	zval *keepSnapshot_param = NULL, *manager;
	zend_bool keepSnapshot;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keepSnapshot_param);

		keepSnapshot = zephir_get_boolval(keepSnapshot_param);


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p2_noret(manager, "keepsnapshots", this_ptr, (keepSnapshot ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the record's snapshot data.
 * This method is used internally to set snapshot data when the model was set up to keep snapshot data
 *
 * @param array data
 * @param array columnMap
 */
PHP_METHOD(Phalcon_Mvc_Model, setSnapshotData) {

	zend_function *_6 = NULL;
	HashTable *_1;
	HashPosition _0;
	zval *data, *columnMap = NULL, *key = NULL, *value = NULL, *snapshot, *attribute = NULL, **_2, *_3 = NULL, *_4 = NULL, *_5 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &data, &columnMap);

	if (!columnMap) {
		ZEPHIR_CPY_WRT(columnMap, ZEPHIR_GLOBAL(global_null));
	}


	if ((Z_TYPE_P(data) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The snapshot data must be an array");
		return;
	}
	if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
		ZEPHIR_INIT_VAR(snapshot);
		array_init(snapshot);
		zephir_is_iterable(data, &_1, &_0, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
			; zend_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HMKEY(key, _1, _0);
			ZEPHIR_GET_HVALUE(value, _2);
			if ((Z_TYPE_P(key) != IS_STRING)) {
				continue;
			}
			ZEPHIR_OBS_NVAR(attribute);
			if (!(zephir_array_isset_fetch(&attribute, columnMap, key TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_3);
				object_init_ex(_3, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_SV(_4, "Column '", key);
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_VS(_5, _4, "' doesn't make part of the column map");
				zephir_call_method_p1_cache_noret(_3, "__construct", &_6, _5);
				zephir_throw_exception(_3 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_array_update_zval(&snapshot, attribute, &value, PH_COPY | PH_SEPARATE);
		}
		zephir_update_property_this(this_ptr, SL("_snapshot"), snapshot TSRMLS_CC);
		RETURN_MM_NULL();
	}
	zephir_update_property_this(this_ptr, SL("_snapshot"), data TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Checks if the object has internal snapshot data
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Mvc_Model, hasSnapshotData) {

	zval *snapshot;


	snapshot = zephir_fetch_nproperty_this(this_ptr, SL("_snapshot"), PH_NOISY_CC);
	if ((Z_TYPE_P(snapshot) == IS_ARRAY)) {
		RETURN_BOOL(1);
	}
	RETURN_BOOL(0);

}

/**
 * Returns the internal snapshot data
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model, getSnapshotData) {


	RETURN_MEMBER(this_ptr, "_snapshot");

}

/**
 * Check if a specific attribute has changed
 * This only works if the model is keeping data snapshots
 *
 * @param string|array fieldName
 */
PHP_METHOD(Phalcon_Mvc_Model, hasChanged) {

	HashTable *_7;
	HashPosition _6;
	zval *fieldName = NULL, *snapshot, *metaData, *columnMap, *allAttributes = NULL, *value = NULL, *originalValue = NULL, *name = NULL, *type = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4, *_5, **_8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &fieldName);

	if (!fieldName) {
		ZEPHIR_CPY_WRT(fieldName, ZEPHIR_GLOBAL(global_null));
	}


	snapshot = zephir_fetch_nproperty_this(this_ptr, SL("_snapshot"), PH_NOISY_CC);
	if ((Z_TYPE_P(snapshot) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The record doesn't have a valid data snapshot");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dirtyState"), PH_NOISY_CC);
	if (!ZEPHIR_IS_LONG(_0, 0)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Change checking cannot be performed because the object has not been persisted or is deleted");
		return;
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(columnMap);
	zephir_call_method_p1(columnMap, metaData, "getreversecolumnmap", this_ptr);
	if ((Z_TYPE_P(columnMap) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(allAttributes);
		zephir_call_method_p1(allAttributes, metaData, "getdatatypes", this_ptr);
	} else {
		ZEPHIR_CPY_WRT(allAttributes, columnMap);
	}
	if ((Z_TYPE_P(fieldName) == IS_ARRAY)) {
		if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
			if (!(zephir_array_isset(columnMap, fieldName))) {
				ZEPHIR_INIT_VAR(_1);
				object_init_ex(_1, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_VAR(_2);
				ZEPHIR_CONCAT_SV(_2, "The field '", fieldName);
				ZEPHIR_INIT_VAR(_3);
				ZEPHIR_CONCAT_VS(_3, _2, "' is not part of the model");
				zephir_call_method_p1_noret(_1, "__construct", _3);
				zephir_throw_exception(_1 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			if (!(zephir_array_isset(allAttributes, fieldName))) {
				ZEPHIR_INIT_NVAR(_1);
				object_init_ex(_1, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_2);
				ZEPHIR_CONCAT_SV(_2, "The field '", fieldName);
				ZEPHIR_INIT_LNVAR(_3);
				ZEPHIR_CONCAT_VS(_3, _2, "' is not part of the model");
				zephir_call_method_p1_noret(_1, "__construct", _3);
				zephir_throw_exception(_1 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
		ZEPHIR_OBS_VAR(value);
		if (!(0)) {
			ZEPHIR_INIT_NVAR(_1);
			object_init_ex(_1, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_LNVAR(_2);
			ZEPHIR_CONCAT_SV(_2, "The field '", fieldName);
			ZEPHIR_INIT_LNVAR(_3);
			ZEPHIR_CONCAT_VS(_3, _2, "' is not defined on the model");
			zephir_call_method_p1_noret(_1, "__construct", _3);
			zephir_throw_exception(_1 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_OBS_VAR(originalValue);
		if (!(zephir_array_isset_fetch(&originalValue, snapshot, fieldName TSRMLS_CC))) {
			ZEPHIR_INIT_NVAR(_1);
			object_init_ex(_1, phalcon_mvc_model_exception_ce);
			ZEPHIR_INIT_VAR(_4);
			ZEPHIR_CONCAT_SV(_4, "The field '", fieldName);
			ZEPHIR_INIT_VAR(_5);
			ZEPHIR_CONCAT_VS(_5, _4, "' was not found in the snapshot");
			zephir_call_method_p1_noret(_1, "__construct", _5);
			zephir_throw_exception(_1 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		RETURN_MM_BOOL(!ZEPHIR_IS_EQUAL(value, originalValue));
	}
	zephir_is_iterable(allAttributes, &_7, &_6, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
		; zend_hash_move_forward_ex(_7, &_6)
	) {
		ZEPHIR_GET_HMKEY(name, _7, _6);
		ZEPHIR_GET_HVALUE(type, _8);
		ZEPHIR_OBS_NVAR(originalValue);
		if (!(zephir_array_isset_fetch(&originalValue, snapshot, name TSRMLS_CC))) {
			RETURN_MM_BOOL(1);
		}
		ZEPHIR_OBS_NVAR(value);
		if (!(0)) {
			RETURN_MM_BOOL(1);
		}
		if (!ZEPHIR_IS_EQUAL(value, originalValue)) {
			RETURN_MM_BOOL(1);
		}
	}
	RETURN_MM_BOOL(0);

}

/**
 * Returns a list of changed values
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model, getChangedFields) {

	HashTable *_2;
	HashPosition _1;
	zval *metaData, *changed, *name = NULL, *type = NULL, *snapshot, *columnMap, *allAttributes = NULL, *value = NULL, *_0, **_3, *_4;

	ZEPHIR_MM_GROW();

	snapshot = zephir_fetch_nproperty_this(this_ptr, SL("_snapshot"), PH_NOISY_CC);
	if ((Z_TYPE_P(snapshot) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The record doesn't have a valid data snapshot");
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_dirtyState"), PH_NOISY_CC);
	if (!ZEPHIR_IS_LONG(_0, 0)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Change checking cannot be performed because the object has not been persisted or is deleted");
		return;
	}
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(columnMap);
	zephir_call_method_p1(columnMap, metaData, "getreversecolumnmap", this_ptr);
	if ((Z_TYPE_P(columnMap) != IS_ARRAY)) {
		ZEPHIR_INIT_VAR(allAttributes);
		zephir_call_method_p1(allAttributes, metaData, "getdatatypes", this_ptr);
	} else {
		ZEPHIR_CPY_WRT(allAttributes, columnMap);
	}
	ZEPHIR_INIT_VAR(changed);
	array_init(changed);
	zephir_is_iterable(allAttributes, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(name, _2, _1);
		ZEPHIR_GET_HVALUE(type, _3);
		if (!(zephir_array_isset(snapshot, name))) {
			zephir_array_append(&changed, name, PH_SEPARATE);
			continue;
		}
		ZEPHIR_OBS_NVAR(value);
		if (!(0)) {
			zephir_array_append(&changed, name, PH_SEPARATE);
			continue;
		}
		zephir_array_fetch(&_4, snapshot, name, PH_NOISY | PH_READONLY TSRMLS_CC);
		if (!ZEPHIR_IS_EQUAL(value, _4)) {
			zephir_array_append(&changed, name, PH_SEPARATE);
			continue;
		}
	}
	RETURN_CCTOR(changed);

}

/**
 * Sets if a model must use dynamic update instead of the all-field update
 *
 *<code>
 *<?php
 *
 *class Robots extends \Phalcon\Mvc\Model
 *{
 *
 *   public function initialize()
 *   {
 *		$this->useDynamicUpdate(true);
 *   }
 *
 *}
 *</code>
 *
 * @param boolean dynamicUpdate
 */
PHP_METHOD(Phalcon_Mvc_Model, useDynamicUpdate) {

	zval *dynamicUpdate_param = NULL, *manager;
	zend_bool dynamicUpdate;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dynamicUpdate_param);

		dynamicUpdate = zephir_get_boolval(dynamicUpdate_param);


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	zephir_call_method_p2_noret(manager, "usedynamicupdate", this_ptr, (dynamicUpdate ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns related records based on defined relations
 *
 * @param string alias
 * @param array arguments
 * @return Phalcon\Mvc\Model\ResultsetInterface
 */
PHP_METHOD(Phalcon_Mvc_Model, getRelated) {

	zval *alias_param = NULL, *arguments = NULL, *manager, *relation, *className, *_0 = NULL, *_1, *_2, *_3, *_4, *_5;
	zval *alias = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &alias_param, &arguments);

		zephir_get_strval(alias, alias_param);
	if (!arguments) {
		ZEPHIR_CPY_WRT(arguments, ZEPHIR_GLOBAL(global_null));
	}


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(className);
	zephir_call_func_p1(className, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(relation);
	zephir_call_method_p2(relation, manager, "getrelationbyalias", className, alias);
	if ((Z_TYPE_P(relation) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "There is no defined relations for the model '", className);
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_VS(_2, _1, "' using alias '");
		ZEPHIR_INIT_VAR(_3);
		concat_function(_3, _2, alias TSRMLS_CC);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_VS(_4, _3, "'");
		zephir_call_method_p1_noret(_0, "__construct", _4);
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_NVAR(_0);
	array_init(_0);
	zephir_array_append(&_0, manager, 0);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_STRING(_5, "getRelationRecords", 1);
	zephir_array_append(&_0, _5, 0);
	ZEPHIR_INIT_BNVAR(_5);
	array_init(_5);
	zephir_array_append(&_5, relation, 0);
	zephir_array_append(&_5, ZEPHIR_GLOBAL(global_null), 0);
	zephir_array_append(&_5, this_ptr, 0);
	zephir_array_append(&_5, arguments, 0);
	zephir_call_func_p2(return_value, "call_user_func_array", _0, _5);
	RETURN_MM();

}

/**
 * Returns related records defined relations depending on the method name
 *
 * @param string modelName
 * @param string method
 * @param array arguments
 * @return mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, _getRelatedRecords) {

	zval *modelName_param = NULL, *method_param = NULL, *arguments, *manager, *relation, *queryMethod, *extraArgs, _0 = zval_used_for_init, *_1 = NULL, *_2 = NULL;
	zval *modelName = NULL, *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &modelName_param, &method_param, &arguments);

		zephir_get_strval(modelName, modelName_param);
		zephir_get_strval(method, method_param);


	manager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(relation);
	ZVAL_BOOL(relation, 0);
	ZEPHIR_INIT_VAR(queryMethod);
	ZVAL_NULL(queryMethod);
	if (zephir_start_with_str(method, SL("get"))) {
		ZEPHIR_SINIT_VAR(_0);
		ZVAL_LONG(&_0, 3);
		ZEPHIR_INIT_VAR(_1);
		zephir_call_func_p2(_1, "substr", method, &_0);
		ZEPHIR_INIT_BNVAR(relation);
		zephir_call_method_p2(relation, manager, "getrelationbyalias", modelName, _1);
	}
	if ((Z_TYPE_P(relation) != IS_OBJECT)) {
		if (zephir_start_with_str(method, SL("count"))) {
			ZEPHIR_INIT_BNVAR(queryMethod);
			ZVAL_STRING(queryMethod, "count", 1);
			ZEPHIR_SINIT_NVAR(_0);
			ZVAL_LONG(&_0, 5);
			ZEPHIR_INIT_NVAR(_1);
			zephir_call_func_p2(_1, "substr", method, &_0);
			ZEPHIR_INIT_VAR(_2);
			ZVAL_STRING(_2, "count", 1);
			ZEPHIR_INIT_BNVAR(relation);
			zephir_call_method_p2(relation, manager, "getrelationbyalias", _2, _1);
		}
	}
	if ((Z_TYPE_P(relation) == IS_OBJECT)) {
		ZEPHIR_OBS_VAR(extraArgs);
		ZEPHIR_INIT_NVAR(_1);
		array_init(_1);
		zephir_array_append(&_1, manager, 0);
		ZEPHIR_INIT_NVAR(_2);
		ZVAL_STRING(_2, "getRelationRecords", 1);
		zephir_array_append(&_1, _2, 0);
		ZEPHIR_INIT_NVAR(_2);
		array_init(_2);
		zephir_array_append(&_2, relation, 0);
		zephir_array_append(&_2, queryMethod, 0);
		zephir_array_append(&_2, this_ptr, 0);
		zephir_array_append(&_2, extraArgs, 0);
		zephir_call_func_p2(return_value, "call_user_func_array", _1, _2);
		RETURN_MM();
	}
	RETURN_MM_NULL();

}

/**
 * Handles method calls when a method is not implemented
 *
 * @param	string method
 * @param	array arguments
 * @return	mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, __call) {

	zval *method_param = NULL, *arguments = NULL, *modelName, *modelsManager, *status, *records, *_0, *_1, *_2, *_3, *_4;
	zval *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &method_param, &arguments);

		zephir_get_strval(method, method_param);
	if (!arguments) {
		ZEPHIR_CPY_WRT(arguments, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(modelName);
	zephir_call_func_p1(modelName, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(records);
	zephir_call_method_p3(records, this_ptr, "_getrelatedrecords", modelName, method, arguments);
	if ((Z_TYPE_P(records) != IS_NULL)) {
		RETURN_CCTOR(records);
	}
	modelsManager = zephir_fetch_nproperty_this(this_ptr, SL("_modelsManager"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(status);
	zephir_call_method_p3(status, modelsManager, "missingmethod", this_ptr, method, arguments);
	if ((Z_TYPE_P(status) != IS_NULL)) {
		RETURN_CCTOR(status);
	}
	ZEPHIR_INIT_VAR(_0);
	object_init_ex(_0, phalcon_mvc_model_exception_ce);
	ZEPHIR_INIT_VAR(_1);
	ZEPHIR_CONCAT_SV(_1, "The method '", method);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VS(_2, _1, "' doesn't exist on model '");
	ZEPHIR_INIT_VAR(_3);
	concat_function(_3, _2, modelName TSRMLS_CC);
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_VS(_4, _3, "'");
	zephir_call_method_p1_noret(_0, "__construct", _4);
	zephir_throw_exception(_0 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Handles method calls when a static method is not implemented
 *
 * @param	string method
 * @param	array arguments
 * @return	mixed
 */
PHP_METHOD(Phalcon_Mvc_Model, __callStatic) {

	zend_class_entry *_7;
	zval *method_param = NULL, *arguments = NULL, *extraMethod, *type = NULL, *modelName, *value, *model, *attributes, *field = NULL, *extraMethodFirst, *metaData, *_0, *_1, _2 = zval_used_for_init, *_3 = NULL, *_4 = NULL, *_5, *_6;
	zval *method = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &method_param, &arguments);

		zephir_get_strval(method, method_param);
	if (!arguments) {
		ZEPHIR_CPY_WRT(arguments, ZEPHIR_GLOBAL(global_null));
	}


	ZEPHIR_INIT_VAR(extraMethod);
	ZVAL_NULL(extraMethod);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "findFirstBy", 1);
	ZEPHIR_INIT_VAR(_1);
	zephir_call_func_p2(_1, "start_with", method, _0);
	if (zephir_is_true(_1)) {
		ZEPHIR_INIT_VAR(type);
		ZVAL_STRING(type, "findFirst", 1);
		ZEPHIR_SINIT_VAR(_2);
		ZVAL_LONG(&_2, 11);
		ZEPHIR_INIT_BNVAR(extraMethod);
		zephir_call_func_p2(extraMethod, "substr", method, &_2);
	}
	if ((Z_TYPE_P(extraMethod) == IS_NULL)) {
		if (zephir_start_with_str(method, SL("findBy"))) {
			ZEPHIR_INIT_NVAR(type);
			ZVAL_STRING(type, "find", 1);
			ZEPHIR_SINIT_NVAR(_2);
			ZVAL_LONG(&_2, 6);
			ZEPHIR_INIT_BNVAR(extraMethod);
			zephir_call_func_p2(extraMethod, "substr", method, &_2);
		}
	}
	if ((Z_TYPE_P(extraMethod) == IS_NULL)) {
		if (zephir_start_with_str(method, SL("countBy"))) {
			ZEPHIR_INIT_NVAR(type);
			ZVAL_STRING(type, "count", 1);
			ZEPHIR_SINIT_NVAR(_2);
			ZVAL_LONG(&_2, 7);
			ZEPHIR_INIT_BNVAR(extraMethod);
			zephir_call_func_p2(extraMethod, "substr", method, &_2);
		}
	}
	ZEPHIR_INIT_VAR(modelName);
	zephir_call_func(modelName, "get_called_class");
	if (zephir_is_true(extraMethod)) {
		ZEPHIR_INIT_BNVAR(_0);
		object_init_ex(_0, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(_3);
		ZEPHIR_CONCAT_SV(_3, "The static method '", method);
		ZEPHIR_INIT_VAR(_4);
		ZEPHIR_CONCAT_VS(_4, _3, "' doesn't exist on model '");
		ZEPHIR_INIT_VAR(_5);
		concat_function(_5, _4, modelName TSRMLS_CC);
		ZEPHIR_INIT_VAR(_6);
		ZEPHIR_CONCAT_VS(_6, _5, "'");
		zephir_call_method_p1_noret(_0, "__construct", _6);
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_OBS_VAR(value);
	if (!(zephir_array_isset_long_fetch(&value, arguments, 0 TSRMLS_CC))) {
		ZEPHIR_INIT_BNVAR(_0);
		object_init_ex(_0, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_LNVAR(_3);
		ZEPHIR_CONCAT_SV(_3, "The static method '", method);
		ZEPHIR_INIT_LNVAR(_4);
		ZEPHIR_CONCAT_VS(_4, _3, "' requires one argument");
		zephir_call_method_p1_noret(_0, "__construct", _4);
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(model);
	_7 = zend_fetch_class(SL("modelName"), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(model, _7);
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, model, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(attributes);
	zephir_call_method_p1(attributes, metaData, "getreversecolumnmap", model);
	if ((Z_TYPE_P(attributes) != IS_ARRAY)) {
		ZEPHIR_INIT_BNVAR(attributes);
		zephir_call_method_p1(attributes, metaData, "getdatatypes", model);
	}
	if (zephir_array_isset(attributes, extraMethod)) {
		ZEPHIR_CPY_WRT(field, extraMethod);
	} else {
		ZEPHIR_INIT_VAR(extraMethodFirst);
		zephir_call_func_p1(extraMethodFirst, "lcfirst", extraMethod);
		if (zephir_array_isset(attributes, extraMethodFirst)) {
			ZEPHIR_CPY_WRT(field, extraMethodFirst);
		} else {
			ZEPHIR_INIT_VAR(field);
			zephir_uncamelize(field, extraMethod);
			if (!(zephir_array_isset(attributes, field))) {
				ZEPHIR_INIT_BNVAR(_0);
				object_init_ex(_0, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_3);
				ZEPHIR_CONCAT_SV(_3, "Cannot resolve attribute '", extraMethod);
				ZEPHIR_INIT_LNVAR(_4);
				ZEPHIR_CONCAT_VS(_4, _3, "' in the model");
				zephir_call_method_p1_noret(_0, "__construct", _4);
				zephir_throw_exception(_0 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	RETURN_MM_NULL();

}

/**
 * Magic method to assign values to the the model
 *
 * @param string property
 * @param mixed value
 */
PHP_METHOD(Phalcon_Mvc_Model, __set) {

	zval *property_param = NULL, *value, *lowerProperty = NULL, *_0;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &property_param, &value);

		zephir_get_strval(property, property_param);


	if ((Z_TYPE_P(value) == IS_OBJECT)) {
		if (zephir_is_instance_of(value, SL("phalcon\\mvc\\modelinterface") TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(lowerProperty);
			zephir_call_func_p1(lowerProperty, "strtolower", property);
			zephir_update_property_zval_zval(this_ptr, lowerProperty, value TSRMLS_CC);
			zephir_update_property_array(this_ptr, SL("_related"), lowerProperty, value TSRMLS_CC);
			ZEPHIR_INIT_ZVAL_NREF(_0);
			ZVAL_LONG(_0, 1);
			zephir_update_property_this(this_ptr, SL("_dirtyState"), _0 TSRMLS_CC);
			RETURN_CCTOR(value);
		}
	}
	if ((Z_TYPE_P(value) == IS_ARRAY)) {
		ZEPHIR_INIT_NVAR(lowerProperty);
		zephir_call_func_p1(lowerProperty, "strtolower", property);
		zephir_update_property_array(this_ptr, SL("_related"), lowerProperty, value TSRMLS_CC);
		ZEPHIR_INIT_ZVAL_NREF(_0);
		ZVAL_LONG(_0, 1);
		zephir_update_property_this(this_ptr, SL("_dirtyState"), _0 TSRMLS_CC);
		RETURN_CCTOR(value);
	}
	zephir_update_property_zval_zval(this_ptr, property, value TSRMLS_CC);
	RETURN_CCTOR(value);

}

/**
 * Magic method to get related records using the relation alias as a property
 *
 * @param string property
 * @return Phalcon\Mvc\Model\Resultset|Phalcon\Mvc\Model
 */
PHP_METHOD(Phalcon_Mvc_Model, __get) {

	zval *property_param = NULL, *modelName, *manager, *lowerProperty, *relation, *result, *_0, *_1 = NULL, *_2, *_3, *_4;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &property_param);

		zephir_get_strval(property, property_param);


	ZEPHIR_INIT_VAR(modelName);
	zephir_call_func_p1(modelName, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(manager);
	zephir_call_method(manager, this_ptr, "getmodelsmanager");
	ZEPHIR_INIT_VAR(lowerProperty);
	zephir_call_func_p1(lowerProperty, "strtolower", property);
	ZEPHIR_INIT_VAR(relation);
	zephir_call_method_p2(relation, manager, "getrelationbyalias", modelName, lowerProperty);
	if ((Z_TYPE_P(relation) == IS_OBJECT)) {
		ZEPHIR_INIT_VAR(_0);
		array_init(_0);
		zephir_array_append(&_0, manager, 0);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "getRelationRecords", 1);
		zephir_array_append(&_0, _1, 0);
		ZEPHIR_INIT_NVAR(_1);
		array_init(_1);
		zephir_array_append(&_1, relation, 0);
		zephir_array_append(&_1, ZEPHIR_GLOBAL(global_null), 0);
		zephir_array_append(&_1, this_ptr, 0);
		zephir_array_append(&_1, ZEPHIR_GLOBAL(global_null), 0);
		ZEPHIR_INIT_VAR(result);
		zephir_call_func_p2(result, "call_user_func_array", _0, _1);
		if ((Z_TYPE_P(result) == IS_OBJECT)) {
			zephir_update_property_zval_zval(this_ptr, lowerProperty, result TSRMLS_CC);
			if (zephir_is_instance_of(result, SL("phalcon\\mvc\\modelinterface") TSRMLS_CC)) {
				zephir_update_property_array(this_ptr, SL("_related"), lowerProperty, result TSRMLS_CC);
			}
		}
		RETURN_CCTOR(result);
	}
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SV(_2, "Access to undefined property ", modelName);
	ZEPHIR_INIT_VAR(_3);
	ZEPHIR_CONCAT_VS(_3, _2, "::");
	ZEPHIR_INIT_VAR(_4);
	concat_function(_4, _3, property TSRMLS_CC);
	zephir_call_func_p1_noret("trigger_error", _4);
	RETURN_MM_NULL();

}

/**
 * Magic method to check if a property is a valid relation
 *
 * @param string property
 */
PHP_METHOD(Phalcon_Mvc_Model, __isset) {

	zval *property_param = NULL, *modelName, *manager, *relation;
	zval *property = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &property_param);

		zephir_get_strval(property, property_param);


	ZEPHIR_INIT_VAR(modelName);
	zephir_call_func_p1(modelName, "get_class", this_ptr);
	ZEPHIR_INIT_VAR(manager);
	zephir_call_method(manager, this_ptr, "getmodelsmanager");
	ZEPHIR_INIT_VAR(relation);
	zephir_call_method_p2(relation, manager, "getrelationbyalias", modelName, property);
	if ((Z_TYPE_P(relation) == IS_OBJECT)) {
		RETURN_MM_BOOL(1);
	}
	RETURN_MM_BOOL(0);

}

/**
 * Serializes the object ignoring connections, services, related objects or static properties
 *
 * @return string
 */
PHP_METHOD(Phalcon_Mvc_Model, serialize) {

	HashTable *_2;
	HashPosition _1;
	zval *data, *metaData, *value = NULL, *attribute = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(data);
	array_init(data);
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method_p1(_0, metaData, "getattributes", this_ptr);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(attribute, _3);
		ZEPHIR_OBS_NVAR(value);
		if (0) {
			zephir_array_update_zval(&data, attribute, &value, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&data, attribute, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		}
	}
	zephir_call_func_p1(return_value, "serialize", data);
	RETURN_MM();

}

/**
 * Unserializes the object from a serialized string
 *
 * @param string data
 */
PHP_METHOD(Phalcon_Mvc_Model, unserialize) {

	HashTable *_2;
	HashPosition _1;
	zval *data, *attributes, *dependencyInjector, *manager, *key = NULL, *value = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &data);



	if ((Z_TYPE_P(data) == IS_STRING)) {
		ZEPHIR_INIT_VAR(attributes);
		zephir_call_func_p1(attributes, "unserialize", data);
		if ((Z_TYPE_P(attributes) == IS_ARRAY)) {
			ZEPHIR_INIT_VAR(dependencyInjector);
			zephir_call_static(dependencyInjector, "Phalcon\\Di", "getdefault");
			if ((Z_TYPE_P(dependencyInjector) != IS_OBJECT)) {
				ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "A dependency injector container is required to obtain the services related to the ORM");
				return;
			}
			zephir_update_property_this(this_ptr, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);
			ZEPHIR_INIT_VAR(_0);
			ZVAL_STRING(_0, "modelsManager", 1);
			ZEPHIR_INIT_VAR(manager);
			zephir_call_method_p1(manager, dependencyInjector, "getshared", _0);
			if ((Z_TYPE_P(manager) != IS_OBJECT)) {
				ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "The injected service 'modelsManager' is not valid");
				return;
			}
			zephir_update_property_this(this_ptr, SL("_modelsManager"), manager TSRMLS_CC);
			zephir_call_method_p1_noret(manager, "initialize", this_ptr);
			zephir_is_iterable(attributes, &_2, &_1, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
				; zend_hash_move_forward_ex(_2, &_1)
			) {
				ZEPHIR_GET_HMKEY(key, _2, _1);
				ZEPHIR_GET_HVALUE(value, _3);
				zephir_update_property_zval_zval(this_ptr, key, value TSRMLS_CC);
			}
			RETURN_MM_NULL();
		}
	}
	ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Invalid serialization data");
	return;

}

/**
 * Returns a simple representation of the object that can be used with var_dump
 *
 *<code>
 * var_dump($robot->dump());
 *</code>
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model, dump) {

	ZEPHIR_MM_GROW();

	zephir_call_func_p1(return_value, "get_object_vars", this_ptr);
	RETURN_MM();

}

/**
 * Returns the instance as an array representation
 *
 *<code>
 * print_r($robot->toArray());
 *</code>
 *
 * @return array
 */
PHP_METHOD(Phalcon_Mvc_Model, toArray) {

	zend_function *_7 = NULL;
	HashTable *_2;
	HashPosition _1;
	zval *data, *metaData, *columnMap, *attribute = NULL, *attributeField = NULL, *value = NULL, *_0, **_3, *_4 = NULL, *_5 = NULL, *_6 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(data);
	array_init(data);
	ZEPHIR_INIT_VAR(metaData);
	zephir_call_method(metaData, this_ptr, "getmodelsmetadata");
	ZEPHIR_INIT_VAR(columnMap);
	zephir_call_method_p1(columnMap, metaData, "getcolumnmap", this_ptr);
	ZEPHIR_INIT_VAR(_0);
	zephir_call_method_p1(_0, metaData, "getattributes", this_ptr);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
		; zend_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(attribute, _3);
		if ((Z_TYPE_P(columnMap) == IS_ARRAY)) {
			ZEPHIR_OBS_NVAR(attributeField);
			if (!(zephir_array_isset_fetch(&attributeField, columnMap, attribute TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(_4);
				object_init_ex(_4, phalcon_mvc_model_exception_ce);
				ZEPHIR_INIT_LNVAR(_5);
				ZEPHIR_CONCAT_SV(_5, "Column '", attribute);
				ZEPHIR_INIT_LNVAR(_6);
				ZEPHIR_CONCAT_VS(_6, _5, "' doesn't make part of the column map");
				zephir_call_method_p1_cache_noret(_4, "__construct", &_7, _6);
				zephir_throw_exception(_4 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} else {
			ZEPHIR_CPY_WRT(attributeField, attribute);
		}
		ZEPHIR_OBS_NVAR(value);
		if (0) {
			zephir_array_update_zval(&data, attributeField, &value, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_update_zval(&data, attributeField, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		}
	}
	RETURN_CCTOR(data);

}

/**
 * Enables/disables options in the ORM
 *
 * @param array options
 */
PHP_METHOD(Phalcon_Mvc_Model, setup) {

	zval *options, *disableEvents, *columnRenaming, *notNullValidations, *exceptionOnFailedSave, *phqlLiterals, *virtualForeignKeys, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &options);



	if ((Z_TYPE_P(options) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_mvc_model_exception_ce, "Options must be an array");
		return;
	}
	ZEPHIR_OBS_VAR(disableEvents);
	if (zephir_array_isset_string_fetch(&disableEvents, options, SS("events") TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "orm.events", 1);
		zephir_call_func_p2_noret("globals_set", _0, disableEvents);
	}
	ZEPHIR_OBS_VAR(virtualForeignKeys);
	if (zephir_array_isset_string_fetch(&virtualForeignKeys, options, SS("virtualForeignKeys") TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "orm.virtual_foreign_keys", 1);
		zephir_call_func_p2_noret("globals_set", _0, virtualForeignKeys);
	}
	ZEPHIR_OBS_VAR(columnRenaming);
	if (zephir_array_isset_string_fetch(&columnRenaming, options, SS("columnRenaming") TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "orm.column_renaming", 1);
		zephir_call_func_p2_noret("globals_set", _0, columnRenaming);
	}
	ZEPHIR_OBS_VAR(notNullValidations);
	if (zephir_array_isset_string_fetch(&notNullValidations, options, SS("notNullValidations") TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "orm.not_null_validations", 1);
		zephir_call_func_p2_noret("globals_set", _0, notNullValidations);
	}
	ZEPHIR_OBS_VAR(exceptionOnFailedSave);
	if (zephir_array_isset_string_fetch(&exceptionOnFailedSave, options, SS("exceptionOnFailedSave") TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "orm.exception_on_failed_save", 1);
		zephir_call_func_p2_noret("globals_set", _0, exceptionOnFailedSave);
	}
	ZEPHIR_OBS_VAR(phqlLiterals);
	if (zephir_array_isset_string_fetch(&phqlLiterals, options, SS("phqlLiterals") TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(_0);
		ZVAL_STRING(_0, "orm.enable_literals", 1);
		zephir_call_func_p2_noret("globals_set", _0, phqlLiterals);
	}
	ZEPHIR_MM_RESTORE();

}

