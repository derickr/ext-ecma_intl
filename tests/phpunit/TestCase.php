<?php

declare(strict_types=1);

namespace Ecma\Test\Intl;

use Mockery;
use Mockery\Adapter\Phpunit\MockeryPHPUnitIntegration;
use Mockery\MockInterface;
use PHPUnit\Framework\TestCase as PHPUnitTestCase;

abstract class TestCase extends PHPUnitTestCase
{
    use MockeryPHPUnitIntegration;

    protected $backupStaticAttributes = false;
    protected $runTestInSeparateProcess = false;

    /**
     * Configures and returns a mock object
     *
     * @param class-string<T> $class
     *
     * @return T & MockInterface
     *
     * @template T
     */
    public function mockery(string $class, mixed ...$arguments)
    {
        /** @var T & MockInterface $mock */
        $mock = Mockery::mock($class, ...$arguments);

        return $mock;
    }
}
